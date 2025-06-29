/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pbc
*/

/**
 * @file event_pbc.c
 * @brief Implements the event for broadcasting a player's message
 * to all graphical clients.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "pbc" message to all connected GUI clients including
 * the player ID and message content.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pbc(server_t *server, player_t *player, char *message)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "pbc #%u %s", player->id, message) == -1)
        logger(server, "PBC", ERROR, true);
    send_to_all_gui(server, buffer);
}
