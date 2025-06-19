/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pfk.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void send_pfk(int fd, unsigned int player_id)
{
    dprintf(fd, "pfk #%u\n", player_id);
}

void event_pfk(server_t *server, player_t *player)
{
    client_t *cl;
    int fd = 0;
    eggs_t *egg;

    egg = create_egg_from_player(player);
    cl = NULL;
    if (!server || !player || !egg)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI != GUI)
            continue;
        fd = server->poll.pollfds[i].fd;
        send_pfk(fd, player->id);
        send_enw(fd, egg);
    }
}
