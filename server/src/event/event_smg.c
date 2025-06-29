/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_smg
*/

/**
 * @file event_smg.c
 * @brief Implements the server message notification event ("smg")
 * for graphical clients.
 * Displays a server-generated message to all GUI clients, typically
 * for informational or administrative purposes.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends an "smg" message to all GUI clients containing a server message.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_smg(server_t *server, char *name)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "SMG %s", name) == -1)
        logger(server, "SMG", ERROR, true);
    send_to_all_gui(server, buffer);
}
