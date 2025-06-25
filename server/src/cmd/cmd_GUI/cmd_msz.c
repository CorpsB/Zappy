/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_msz.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_msz(server_t *server, int index, char **args)
{
    int fd;

    (void)args;
    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    fd = server->poll.pollfds[index].fd;
    dprintf(fd, "msz %u %u\n", server->width, server->height);
}
