/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pfk.c
*/

/**
 * @file event_pfk.c
 * @brief Implements the player laying an egg event ("pfk") and triggers egg
 * creation notification.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "pfk" message to all graphical clients when a player lays an egg.
 * Then triggers the event_enw() to notify creation of the new egg.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pfk(server_t *server, player_t *player)
{
    char *buffer = NULL;

    if (!server || !player)
        return;
    if (asprintf(&buffer, "pfk #%u", player->id) == -1)
        logger(server, "PFK", ERROR, true);
    send_to_all_gui(server, buffer);
    event_enw(server, player);
}
