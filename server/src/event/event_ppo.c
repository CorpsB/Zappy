/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_ppo.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void send_ppo(int fd, player_t *player)
{
    if (!player)
        return;
    dprintf(fd, "ppo #%u %u %u %u\n", player->id, player->position[0],
        player->position[1], player->direction);
}

void event_ppo(server_t *server, player_t *player)
{
    client_t *cl;
    int fd;

    if (!server || !player || player->is_dead)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI != GUI)
            continue;
        fd = server->poll.pollfds[i].fd;
        send_ppo(fd, player);
    }
}
