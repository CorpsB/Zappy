/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_ppo.c
*/

/**
 * @file event_ppo.c
 * @brief Implements the player position notification event ("ppo")
 * for graphical clients.
 * Sends player coordinates and direction information to all GUI clients,
 * allowing real-time map updates.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "ppo" message to all GUI clients containing a player's ID,
 * position, and direction.
 * Typically used to update the graphical representation of player movements.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_ppo(server_t *server, player_t *player)
{
    char *buffer = NULL;

    if (!server || !player || player->is_dead)
        return;
    if (asprintf(&buffer, "ppo #%u %u %u %u",
        player->id, player->position[0],
        player->position[1], player->direction) == -1)
        logger(server, "PPO", ERROR, true);
    send_to_all_gui(server, buffer);
}
