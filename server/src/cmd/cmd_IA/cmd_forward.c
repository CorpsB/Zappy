/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_salut.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Move the player one tile forward according to their
 * current direction.
 * This function handles map wrapping: if the player reaches the
 * edge of the map,
 * they reappear on the opposite side.
 * @param server Pointer to the global server structure.
 * @param player Pointer to the player structure to update.
*/
static void move_player_forward(server_t *server, player_t *player)
{
    if (player->direction == NORTH)
        player->position[1] = (player->position[1] + 1) % server->height;
    if (player->direction == SOUTH)
        player->position[1] =
            (player->position[1] + server->height - 1) % server->height;
    if (player->direction == EAST)
        player->position[0] = (player->position[0] + 1) % server->width;
    if (player->direction == WEST)
        player->position[0] =
            (player->position[0] + server->width - 1) % server->width;
}

void cmd_forward(server_t *server, int index, char **args)
{
    player_t *player;

    (void)args;
    player = server->poll.client_list[index].player;
    if (!player || player->is_dead)
        return;
    move_player_forward(server, player);
    event_ppo(server, player);
    dprintf(server->poll.pollfds[index].fd, "ok\n");
}
