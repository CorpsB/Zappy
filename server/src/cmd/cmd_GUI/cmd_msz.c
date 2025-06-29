/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_msz.c
*/

/**
 * @file cmd_msz.c
 * @brief Implements the "msz" graphical command for the Zappy server.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * This file handles the "msz" command, which provides the dimensions of the
 * map (width and height) to graphical clients upon request.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_msz(server_t *server, int index, char **args)
{
    int fd;
    char *buffer = NULL;

    (void)args;
    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    fd = server->poll.pollfds[index].fd;
    if (asprintf(&buffer, "msz %u %u\n", server->width, server->height) == -1)
        logger(server, "ASPRINTF : MSZ", PERROR, true);
    send_str(server, fd, buffer, true);
}
