/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pdi.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pdi(server_t *server, player_t *player, bool is_open)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "pdi #%d", player->id) == -1)
        logger(server, "PDI", ERROR, true);
    send_to_all_gui(server, buffer);
    if (is_open)
        send_str(server, player->socket_fd, "dead\n", false);
}

void event_pdi_by_index(server_t *server, int index)
{
    if (server->poll.client_list[index].whoAmI == PLAYER)
        event_pdi(server, server->poll.client_list[index].player, false);
}
