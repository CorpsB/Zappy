/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_sbp
*/

/**
 * @file event_sbp.c
 * @brief Implements the incorrect argument error notification event ("sbp")
 * for graphical clients.
 * Provides feedback when a GUI client sends a command with an invalid number
 * or format of arguments.
 * Includes optional debug information if enabled on the server.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends an "sbp" message to the concerned GUI client to indicate invalid
 * command arguments.
 * If debug mode is enabled, detailed information about the command and
 * argument mismatch is logged.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/cmd.h"
#include "include/cmd_parser_table.h"

static void send_sbp(server_t *server, int, char **args, int i)
{
    char *buffer = NULL;

    if (printf("CMD : %s\tARGS SIZE : %u\tEXPECTED SIZE : %u\n\n",
        gui_command_table[i].name,
        table_size(args),
        gui_command_table[i].argument_nbr) == -1)
        logger(server, "PRINTF : SBP", PERROR, true);
    if (asprintf(&buffer,
        "CMD : %s\t ARGS SIZE : %u\tEXPECTED SIZE : %u\n\n",
        gui_command_table[i].name,
        table_size(args),
        gui_command_table[i].argument_nbr) == -1)
        logger(server, "ASPRINTF : SBP DEBUG", PERROR, true);
    if (dprintf(server->debug_fd, "%s\n", buffer) == -1)
        logger(server, "DPRINTF : SBP", PERROR, true);
}

void event_sbp(server_t *server, int index, char **args, int i)
{
    if (!server)
        return;
    send_str(server, server->poll.pollfds[index].fd, "sbp\n", false);
    logger(server, "INVALID ARGS OR ARGS NUMBER FOR THIS COMMAND",
        INFO, false);
    if (server->debug) {
        send_sbp(server, index, args, i);
    }
}
