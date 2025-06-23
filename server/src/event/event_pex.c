/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pex
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pex(server_t *server, player_t *player)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "pex #%u", player->id) == -1)
        logger(server, "PEX", ERROR, true);
    send_to_all_gui(server, buffer);
    if (buffer)
        free(buffer);
}