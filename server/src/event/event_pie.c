/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** event_pie
*/

/**
 * @file event_pie.c
 * @brief Implements the incantation result notification event ("pie") for
 * graphical clients.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "pie" message to all GUI clients to indicate the result of an
 * incantation at a specific position.
 * The message specifies the coordinates and whether the incantation
 * succeeded (1) or failed (0).
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/incantation_table.h"

void event_pie(server_t *server, player_t *player, bool succes)
{
    char *message = NULL;

    if (!succes) {
        if (asprintf(&message, "pie %u %u %u", player->position[0],
            player->position[1], 0) == -1) {
            logger(server, "ASPRINTF : PIE", PERROR, true);
        }
    } else {
        if (asprintf(&message, "pie %u %u %u", player->position[0],
            player->position[1], 1) == -1) {
            logger(server, "ASPRINTF : PIE", PERROR, true);
        }
    }
    send_to_all_gui(server, message);
}
