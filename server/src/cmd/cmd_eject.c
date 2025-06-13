/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_eject.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Push @p pl one tile in @p dir, wrapping on map edges,
 *        and set his new facing direction to @p dir.
*/
static void push_player(player_t *pl, direction_t dir,
    unsigned int width, unsigned int height)
{
    switch (dir) {
    case NORTH:
        pl->position[1] = (pl->position[1] + height - 1) % height;
        break;
    case SOUTH:
        pl->position[1] = (pl->position[1] + 1) % height;
        break;
    case EAST:
        pl->position[0] = (pl->position[0] + 1) % width;
        break;
    case WEST:
        pl->position[0] = (pl->position[0] + width - 1) % width;
        break;
    default:
        break;
    }
    pl->direction = dir;
}

/**
 * @brief Push every player of @p team that shares the tile (x,y)
 *        with @p agressor, except @p agressor itself.
*/
static unsigned eject_team(teams_t *team, const player_t *agressor,
    unsigned int width, unsigned int height)
{
    unsigned pushed = 0;

    for (player_t *p = team->player; p; p = p->next) {
        if (p == agressor)
            continue;
        if (p->position[0] == agressor->position[0] &&
            p->position[1] == agressor->position[1]) {
            push_player(p, agressor->direction, width, height);
            pushed++;
        }
    }
    return pushed;
}

void cmd_eject(server_t *server, int index, const char **args)
{
    client_t *cl;
    player_t *aggressor;
    unsigned total = 0;
    int fd;

    (void)args;
    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    cl = &server->poll.client_list[index];
    fd = server->poll.pollfds[index].fd;
    if (cl->whoAmI != PLAYER || !cl->player) {
        dprintf(fd, "ko\n");
        return;
    }
    aggressor = cl->player;
    for (teams_t *t = server->teams; t; t = t->next)
        total += eject_team(t, aggressor, server->width, server->height);
    dprintf(aggressor->socket_fd, total ? "ok\n" : "ko\n");
}
