/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pbc
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pbc(server_t *server, player_t *player, char *message)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "pbc #%u %s", player->id, message) == -1)
        logger(server, "PBC", ERROR, true);
    send_to_all_gui(server, buffer);
    if (buffer)
        free(buffer);
}