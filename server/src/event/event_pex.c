/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pex
*/

/**
 * @file event_pex.c
 * @brief Implements player level-up (expulsion) notification event.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "pex" message to all GUI clients indicating a player
 * performed an expulsion action.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pex(server_t *server, player_t *player)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "pex #%u", player->id) == -1)
        logger(server, "PEX", ERROR, true);
    send_to_all_gui(server, buffer);
    if (buffer)
        free(buffer);
}
