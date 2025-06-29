/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_suc
*/

/**
 * @file event_suc.c
 * @brief Implements the unknown command error notification event
 * ("suc") for graphical clients.
 * Informs a GUI client that the command they sent is unrecognized
 * or invalid.
 * Also logs the incorrect command on the server for debugging purposes.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "suc" message to the concerned GUI client to indicate an
 * unknown command.
 * The incorrect command is logged for server-side diagnostics.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_suc(server_t *server, int index, char **args)
{
    send_str(server, server->poll.pollfds[index].fd, "suc\n", false);
    logger(server, "UNKNOW GUI COMMAND:", INFO, false);
    logger(server, args[0], INFO, false);
}
