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

static bool is_new_player(server_t *server, int index, char *cmd)
{
    for (teams_t *team = server->teams; team != NULL; team = team->next)
        if (strncmp(cmd, team->name, strlen(team->name)) == 0) {
            cmd_player(server, index, team);
            return true;
        }
    return false;
}

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

static void gui_args_checker(server_t *server, int index, char **args,
    int i)
{
    if (table_size(args) != gui_command_table[i].argument_nbr) {
        event_sbp(server, index, args, i);
    } else {
        gui_command_table[i].func(server, index, args);
    }
}

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
