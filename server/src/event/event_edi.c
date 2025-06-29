/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_edi.c
*/

/**
 * @file event_edi.c
 * @brief Implements the event to notify graphical clients that an egg
 * has hatched.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends the "edi" event with the egg ID to all GUI clients,
 * informing them that an egg has hatched and transformed into a player.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_edi(server_t *server, unsigned int egg_id)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "edi #%u", egg_id) == -1)
        logger(server, "EDI", ERROR, true);
    send_to_all_gui(server, buffer);
}
