/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_right.c
*/

/**
 * @file cmd_right.c
 * @brief Implements the "right" command to rotate a player 90 degrees
 * clockwise.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Rotates the player's facing direction clockwise through the sequence:
 * NORTH → EAST → SOUTH → WEST → NORTH.
 * Sends an "ok" response and triggers the appropriate update event.
 * Ensures the command is ignored if the player is dead or invalid.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Rotate the player 90 degrees to the right (clockwise).
 * Updates the player's direction according to the standard rotation:
 * NORTH → EAST → SOUTH → WEST → NORTH.
 * @param p Pointer to the player structure to update.
*/
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
    send_str(server, server->poll.pollfds[index].fd, "ok\n", false);
}
