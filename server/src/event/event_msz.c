/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_msz
*/

/**
 * @file event_msz.c
 * @brief Implements the event to send the map size to graphical clients.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends the map size using the "msz" protocol message to all
 * connected GUI clients.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_msz(server_t *server)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "msz %u %u", server->width, server->height) == -1)
        logger(server, "MSZ", ERROR, true);
    send_to_all_gui(server, buffer);
}
