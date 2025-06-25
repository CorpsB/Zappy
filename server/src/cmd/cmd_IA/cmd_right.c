/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_right.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void rotate_right(player_t *p)
{
    switch (p->direction) {
        case NORTH:
            p->direction = EAST;
            break;
        case EAST:
            p->direction = SOUTH;
            break;
        case SOUTH:
            p->direction = WEST;
            break;
        case WEST:
            p->direction = NORTH;
            break;
        default:
            break;
    }
}

void cmd_right(server_t *server, int index, char **args)
{
    player_t *p;

    (void)args;
    p = server->poll.client_list[index].player;
    if (!p || p->is_dead)
        return;
    rotate_right(p);
    event_ppo(server, p);
    dprintf(server->poll.pollfds[index].fd, "ok\n");
}
