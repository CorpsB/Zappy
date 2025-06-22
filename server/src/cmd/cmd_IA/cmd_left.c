/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_left.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void rotate_left(player_t *p)
{
    switch (p->direction) {
        case NORTH:
            p->direction = WEST;
            break;
        case WEST:
            p->direction = SOUTH;
            break;
        case SOUTH:
            p->direction = EAST;
            break;
        case EAST:
            p->direction = NORTH;
            break;
        default:
            break;
    }
}

void cmd_left(server_t *server, int index, char **args)
{
    player_t *p;

    (void)args;
    if (check_autorized(server, index) != 0)
        return;
    p = server->poll.client_list[index].player;
    if (!p || p->is_dead)
        return;
    rotate_left(p);
    event_ppo(server, p);
    dprintf(server->poll.pollfds[index].fd, "ok\n");
}
