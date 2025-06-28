/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_sgt_T.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_sgt(server_t *server, int index, char **args)
{
    int fd;

    (void)args;
    fd = server->poll.pollfds[index].fd;
    dprintf(fd, "sgt %u\n", server->frequency);
}
