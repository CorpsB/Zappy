/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pnw.c
*/

/**
 * @file event_pnw.c
 * @brief Implements the player connection notification event ("pnw")
 * for graphical clients.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "pnw" message to all GUI clients when a new player connects to
 * the game.
 * The message contains the player's ID, position, direction, level, and
 * team name.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pnw(server_t *server, player_t *player)
{
    char *buffer = NULL;

    if (!server || !player || !player->team)
        return;
    if (asprintf(&buffer, "pnw #%u %u %u %d %u %s",
        player->id, player->position[0], player->position[1],
        player->direction, player->lvl, player->team->name) == -1)
        logger(server, "PNW", ERROR, true);
    send_to_all_gui(server, buffer);
}
