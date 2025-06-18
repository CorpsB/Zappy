/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_fork.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_fork(server_t *server, int index, char **args)
{
    player_t *pl;

    (void)args;
    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    if (check_autorized(server, index) != 0)
        return;
    pl = server->poll.client_list[index].player;
    add_eggs(server, pl->id, pl->team, pl->position);
    dprintf(pl->socket_fd, "ok\n");
}
