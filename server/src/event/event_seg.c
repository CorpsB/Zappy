/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_seg
*/

/**
 * @file event_seg.c
 * @brief Implements the game end notification event ("seg")
 * for graphical clients.
 * Indicates the winning team at the end of the game to all GUI clients.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "seg" message to all GUI clients specifying the name of
 * the winning team.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_seg(server_t *server, char *name)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "seg %s", name) == -1)
        logger(server, "SEG", ERROR, true);
    send_to_all_gui(server, buffer);
}
