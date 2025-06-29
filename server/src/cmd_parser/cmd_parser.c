/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_parser
*/

/**
 * @file cmd_parser.c
 * @brief Handles parsing and execution of client commands for Zappy server.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * This file implements the logic to parse and dispatch incoming commands
 * from players and graphical clients. It handles unknown clients,
 * validates arguments, and ensures correct command execution.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/cmd.h"
#include "include/cmd_parser_table.h"

/**
 * @brief Frees the given command string.
 * @param cmd The command string to free.
*/
static void free_cmd(char *cmd)
{
    if (cmd) {
        free(cmd);
        cmd = NULL;
    }
}

/**
 * @brief Checks if the given command matches a known team name.
 * @param server The server structure.
 * @param index The index of the client in the pollfd list.
 * @param cmd The received command.
 * @return true if the command matches a team name and the player
 * is handled, false otherwise.
*/
static bool is_new_player(server_t *server, int index, char *cmd)
{
    for (teams_t *team = server->teams; team != NULL; team = team->next)
        if (strncmp(cmd, team->name, strlen(team->name)) == 0) {
            cmd_player(server, index, team);
            return true;
        }
    return false;
}

/**
 * @brief Handles the authentication of an unknown client.
 * @param server The server structure.
 * @param index The index of the client in the pollfd list.
 * @param cmd The received command.
 * @return true if the client is recognized as a GUI or new player,
 * false otherwise.
*/
static bool unknown_client(server_t *server, int index, char *cmd)
{
    if (strncmp(cmd, "GRAPHIC", 7) == 0) {
        cmd_graphic(server, index, NULL);
        logger(server, "NEW GUI CLIENT FOUND.", INFO, false);
        return true;
    }
    if (is_new_player(server, index, cmd)) {
        logger(server, "NEW PLAYER FOUND.", INFO, false);
        return true;
    }
    return false;
}

/**
 * @brief Parses the command of an unknown client.
 * @param server The server structure.
 * @param index The index of the client in the pollfd list.
 * @param cmd The received command.
 * @details If the client is not recognized, sends a "ko" message
 * and logs the attempt.
*/
static void parse_unknown_client(server_t *server, int index, char *cmd)
{
    if (!unknown_client(server, index, cmd)) {
        send_str(server, server->poll.pollfds[index].fd, "ko\n", false);
        logger(server, "UNKNOWN CLIENT SEND CMD BEFORE AUTHENTIFICATION CMD:",
        INFO, false);
        logger(server, cmd, INFO, false);
        return;
    }
}

/**
 * @brief Checks the arguments of a GUI command and executes it if valid.
 * @param server The server structure.
 * @param index The index of the client in the pollfd list.
 * @param args The array of command arguments.
 * @param i The index of the command in the GUI command table.
*/
static void gui_args_checker(server_t *server, int index, char **args,
    int i)
{
    if (table_size(args) != gui_command_table[i].argument_nbr) {
        event_sbp(server, index, args, i);
    } else {
        gui_command_table[i].func(server, index, args);
    }
}

/**
 * @brief Parses a command sent by a GUI client.
 * @param server The server structure.
 * @param index The index of the client in the pollfd list.
 * @param args The array of command arguments.
 * @details If the command is unknown, sends an "suc" event to the GUI client.
*/
static void parse_gui_client(server_t *server, int index, char **args)
{
    if (!args[0]) {
        logger(server, "Command found, but str_to_array errors.",
            ERROR, false);
        return;
    }
    for (int i = 0; gui_command_table[i].name != NULL; i++) {
        if (strncmp(args[0], gui_command_table[i].name,
            strlen(gui_command_table[i].name)) == 0) {
            gui_args_checker(server, index, args, i);
            return;
        }
    }
    event_suc(server, index, args);
}

/**
 * @brief Sends a debug message to a player client when
 * incorrect arguments are detected.
 * @param server The server structure.
 * @param index The index of the client in the pollfd list.
 * @param args The array of command arguments.
 * @param i The index of the command in the player command table.
*/
static void send_debug_message(server_t *server, int index,
    char **args, int i)
{
    char *buffer = NULL;

    if (printf("CMD : %s\tARGS SIZE : %u\tEXPECTED SIZE : %u\n\n",
        player_command_table[i].name, table_size(args),
        player_command_table[i].argument_nbr) == -1)
            logger(server, "PRINTF CMD PARSER", PERROR, true);
    if (asprintf(&buffer,
        "CMD : %s\t ARGS SIZE : %u\tEXPECTED SIZE : %u\n\n",
        player_command_table[i].name, table_size(args),
        player_command_table[i].argument_nbr) == -1)
        logger(server, "ASPRINTF : ARG CHECKER", PERROR, true);
    send_str(server, server->poll.pollfds[index].fd, buffer, true);
}

/**
 * @brief Checks the arguments of a player command and executes it if valid.
 * @param server The server structure.
 * @param index The index of the client in the pollfd list.
 * @param args The array of command arguments.
 * @param i The index of the command in the player command table.
 * @details Sends a "ko" message if arguments are invalid and debug
 * mode is enabled.
*/
static void player_args_checker(server_t *server, int index,
    char **args, int i)
{
    if (table_size(args) == player_command_table[i].argument_nbr ||
        player_command_table[i].argument_nbr == -1) {
        player_command_table[i].func(server, index, args);
        return;
    }
    send_str(server, server->poll.pollfds[index].fd, "ko\n", false);
    logger(server, "INVALID ARGS NUMBER FOR THIS COMMAND", INFO, false);
    if (server->debug)
        send_debug_message(server, index, args, i);
}

/**
 * @brief Parses a command sent by a player client.
 * @param server The server structure.
 * @param index The index of the client in the pollfd list.
 * @param args The array of command arguments.
 * @details If the command is unknown, sends a "ko" message to the player.
*/
static void parse_player_client(server_t *server, int index, char **args)
{
    if (!args[0]) {
        logger(server, "Command found, but str_to_array errors.",
            ERROR, false);
        return;
    }
    for (int i = 0; player_command_table[i].name != NULL; i++) {
        if (strncmp(args[0], player_command_table[i].name,
            strlen(player_command_table[i].name)) == 0) {
            player_args_checker(server, index, args, i);
            return;
        }
    }
    send_str(server, server->poll.pollfds[index].fd, "ko\n", false);
    logger(server, "UNKNOW PLAYER COMMAND:", INFO, false);
    logger(server, args[0], INFO, false);
}

void cmd_parser(server_t *server, int index, char *cmd)
{
    char **args = str_to_array(cmd, " ");

    if (server->poll.client_list[index].whoAmI == UNKNOWN) {
        parse_unknown_client(server, index, cmd);
        free_table(args);
        return;
    }
    free_cmd(cmd);
    if (server->poll.client_list[index].whoAmI == GUI) {
        parse_gui_client(server, index, args);
        free_table(args);
        return;
    }
    if (server->poll.client_list[index].whoAmI == PLAYER) {
        parse_player_client(server, index, args);
        free_table(args);
        return;
    }
    logger(server, "Unknown type of client send a command.", ERROR, false);
}
