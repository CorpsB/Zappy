/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_plv
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_plv(server_t *server, player_t *player)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "plv #%u %u", player->id, player->lvl) == -1)
        logger(server, "PLV", ERROR, true);
    send_to_all_gui(server, buffer);
}

void event_all_plv(server_t *server)
{
    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI == PLAYER)
            event_plv(server, server->poll.client_list[i].player);
    }
}
