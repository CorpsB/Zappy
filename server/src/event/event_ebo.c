/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_ebo.c
*/

/**
 * @file event_ebo.c
 * @brief Implements the event to notify graphical clients of a new
 * egg laid in the game.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends the "ebo" event with the egg ID to all GUI clients,
 * informing them that a new egg has been created on the map.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_ebo(server_t *server, unsigned int egg_id)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "ebo #%u", egg_id) == -1)
        logger(server, "EBO", ERROR, true);
    send_to_all_gui(server, buffer);
}
