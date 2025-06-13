/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_fork.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Add an egg at the exact (x, y) position of the given player.
 *
 * @param server Global server pointer (for id & counters).
 * @param pl     Pointer to the player who lays the egg.
 * @param x      X coordinate.
 * @param y      Y coordinate.
*/
static void add_egg_at(server_t *server, const player_t *pl, unsigned int x,
    unsigned int y)
{
    eggs_t *node = malloc(sizeof(*node));

    if (!node) {
        perror("[ERROR] - malloc");
        exit(84);
    }
    node->id = server->eggs_count;
    node->creator_id = pl->id;
    node->position[0] = x;
    node->position[1] = y;
    node->next = pl->team->egg;
    pl->team->egg = node;
    server->eggs_count++;
}

void cmd_fork(server_t *server, int index, const char *args)
{
    player_t *pl;

    if (!server || !server->poll.client_list ||
        !server->poll.client_list[index].player)
        return;
    pl = server->poll.client_list[index].player;
    add_egg_at(server, pl, pl->position[0], pl->position[1]);
    pl->team->slots_used++;
    dprintf(pl->socket_fd, "ok\n");
    //envoyer à la GUI ?
}
