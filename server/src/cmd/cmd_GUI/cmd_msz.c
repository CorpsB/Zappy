/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_msz.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

int check_graphical(server_t *server, int index)
{
    client_t *cl;
    int fd;

    cl = &server->poll.client_list[index];
    fd = server->poll.pollfds[index].fd;
    if (cl->whoAmI != GUI) {
        dprintf(fd, "ko\n");
        return 1;
    }
    return 0;
}

void cmd_msz(server_t *server, int index, char **args)
{
    int fd;

    (void)args;
    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    if (check_graphical(server, index) != 0)
        return;
    fd = server->poll.pollfds[index].fd;
    //dprintf(fd, "msz %u %u\n", server->width, server->height);
    dprintf(fd, "voici la map\n");
}
