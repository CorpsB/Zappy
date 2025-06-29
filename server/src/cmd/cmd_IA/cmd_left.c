/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_left.c
*/

/**
 * @file cmd_left.c
 * @brief Implements the "left" command to rotate a player 90 degrees
 * counterclockwise.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Rotates the player left by updating their direction counterclockwise
 * (NORTH → WEST → SOUTH → EAST → NORTH).
 * Sends an acknowledgment "ok" response and triggers position update events.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Rotate the player 90 degrees to the left (counterclockwise).
 * Updates the player's direction according to the standard rotation:
 * NORTH → WEST → SOUTH → EAST → NORTH.
 * @param p Pointer to the player structure to update.
*/
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
    p = server->poll.client_list[index].player;
    if (!p || p->is_dead)
        return;
    rotate_left(p);
    event_ppo(server, p);
    send_str(server, server->poll.pollfds[index].fd, "ok\n", false);
}
