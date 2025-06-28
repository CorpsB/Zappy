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

static void remove_eggs_in_team(teams_t *team, unsigned x, unsigned y,
    server_t *server)
{
    eggs_t **pp;
    eggs_t *e;

    if (!team)
        return;
    pp = &team->egg;
    e = *pp;
    while (e) {
        if (e->position[0] == x && e->position[1] == y) {
            *pp = e->next;
            free(e);
            server->eggs_count--;
            e = *pp;
            continue;
        }
        pp = &e->next;
        e = *pp;
    }
}

/** Destroy every egg located at (x,y) on the whole map. */
static void destroy_eggs(server_t *server, unsigned x, unsigned y)
{
    teams_t *t = server->teams;

    while (t) {
        remove_eggs_in_team(t, x, y, server);
        t = t->next;
    }
}

/** Notify the player, push him, then destroy eggs on his new tile. */
static void notify_and_push(player_t *pl, direction_t dir,
    server_t *server)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "Eject %d\n", dir) == -1)
        logger(server, "ASPRINTF : Eject", PERROR, true);
    send_str(server, pl->socket_fd, buffer);
    push_player(pl, dir, server->width, server->height);
    destroy_eggs(server, pl->position[0], pl->position[1]);
}

/**
 * @brief Push every player of @p team that shares the tile (x,y)
 *        with @p agressor, except @p agressor itself.
 *  Push every player of @p team sharing the tile with @p agressor
 * (except @p a).
*/
static unsigned eject_team(teams_t *team, const player_t *agressor,
    server_t *server)
{
    unsigned pushed = 0;
    player_t *p;

    for (p = team->player; p; p = p->next) {
        if (p == agressor)
            continue;
        if (p->position[0] == agressor->position[0] &&
            p->position[1] == agressor->position[1]) {
            notify_and_push(p, agressor->direction, server);
            pushed++;
        }
    }
    return pushed;
}

static void send_ko(server_t *server, int fd)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "ko\n") == -1)
        logger(server, "ASPRINTF : EJECT KO", PERROR, true);
    send_str(server, fd, buffer);
}

static void send_eject_response(server_t *server, player_t *ag, unsigned total)
{
    char *buffer = NULL;

    if (asprintf(&buffer, total ? "ok\n" : "ko\n") == -1)
        logger(server, "ASPRINTF : EJECT RESPONSE", PERROR, true);
    send_str(server, ag->socket_fd, buffer);
}

void cmd_eject(server_t *server, int index, const char **args)
{
    client_t *cl;
    player_t *ag;
    unsigned total = 0;
    int fd;

    (void)args;
    if (!server || index < 0 || index >= server->poll.client_index)
        return;
    cl = &server->poll.client_list[index];
    fd = server->poll.pollfds[index].fd;
    if (cl->whoAmI != PLAYER || !cl->player)
        return send_ko(server, fd);
    ag = cl->player;
    for (teams_t *t = server->teams; t; t = t->next)
        total += eject_team(t, ag, server);
    send_eject_response(server, ag, total);
    if (total)
        event_pex(server, ag);
}
