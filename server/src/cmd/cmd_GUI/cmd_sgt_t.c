/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_sgt_T.c
*/

/**
 * @file cmd_sgt.c
 * @brief Implements the "sgt" graphical command for the Zappy server.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * Handles the "sgt" command, which requests the current game frequency
 * (ticks per second) from the server. The server replies with:
 * "sgt <frequency>"
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_sgt(server_t *server, int index, char **args)
{
    int fd;
    char *buffer = NULL;

    (void)args;
    fd = server->poll.pollfds[index].fd;
    if (asprintf(&buffer, "sgt %u\n", server->frequency) == -1)
        logger(server, "ASPRINTF : SGT", PERROR, true);
    send_str(server, fd, buffer, true);
}
