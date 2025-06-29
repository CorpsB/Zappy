/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pin.c
*/

/**
 * @file event_pin.c
 * @brief Implements the player inventory notification event ("pin") for
 * graphical clients.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "pin" message to all GUI clients containing detailed information
 * about a player's position and inventory.
 * The message includes player ID, position coordinates, and quantities of
 * each resource carried by the player.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pin(server_t *server, player_t *player)
{
    char *buffer = NULL;

    if (!server || !player || player->is_dead)
        return;
    if (asprintf(&buffer,
        "pin #%u %u %u %u %u %u %u %u %u %u",
        player->id, player->position[0], player->position[1],
        player->inventory.food, player->inventory.linemate,
        player->inventory.deraumere, player->inventory.sibur,
        player->inventory.mendiane, player->inventory.phiras,
        player->inventory.thystame) == -1)
        logger(server, "PIN", ERROR, true);
    send_to_all_gui(server, buffer);
}
