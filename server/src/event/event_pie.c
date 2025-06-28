/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** event_pie
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/incantation_table.h"

void event_pie(server_t *server, player_t *player, bool succes)
{
    char *message = NULL;

    if (!succes) {
        if (asprintf(&message, "pie %u %u %u", player->position[1],
            player->position[0], 0) == -1) {
            logger(server, "ASPRINTF : PIE", PERROR, true);
        }
    } else {
        if (asprintf(&message, "pie %u %u %u", player->position[1],
            player->position[0], 1) == -1) {
            logger(server, "ASPRINTF : PIE", PERROR, true);
        }
    }
    send_to_all_gui(server, message);
            
}
