/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_tna.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_tna(server_t *server, int index, char **args)
{
    int fd;
    teams_t *team;

    (void)args;
    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    if (check_graphical(server, index) != 0)
        return;
    fd = server->poll.pollfds[index].fd;
    for (team = server->teams; team; team = team->next) {
        if (team->name)
            dprintf(fd, "tna %s\n", team->name);
    }
}
