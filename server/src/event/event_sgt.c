/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_sgt.c
*/

/**
 * @file event_sgt.c
 * @brief Implements the time unit frequency notification event ("sgt") for
 * graphical clients.
 * Provides the current time unit frequency used in the game to all GUI
 * clients.
 * This frequency determines the speed of game actions.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "sgt" message to all GUI clients indicating the game's current
 * frequency setting.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_sgt(server_t *server)
{
    char *buffer = NULL;

    if (!server)
        return;
    if (asprintf(&buffer, "sgt %u", server->frequency) == -1)
        logger(server, "SGT", ERROR, true);
    send_to_all_gui(server, buffer);
}
