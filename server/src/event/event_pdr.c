/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pdr
*/

/**
 * @file event_pdr.c
 * @brief Implements the event for player dropping a resource notification.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "pdr" message to all GUI clients to notify that a player
 * dropped a resource.
 * The resource type is specified by an enum.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pdr(server_t *server, int id, r_ressource_t type)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "pdr #%u %u", id, (int)type) == -1)
        logger(server, "PDR PER TILE", ERROR, true);
    send_to_all_gui(server, buffer);
}
