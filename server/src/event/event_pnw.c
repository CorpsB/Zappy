/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pnw.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pnw(server_t *server, player_t *player)
{
    client_t *cl;
    int fd;

    fd = 0;
    if (!server || !player || !player->team)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI != GUI)
            continue;
        fd = server->poll.pollfds[i].fd;
        dprintf(fd, "pnw #%u %u %u %d %u %s\n", player->id,
            player->position[0], player->position[1], player->direction,
            player->lvl, player->team->name);
    }
}
