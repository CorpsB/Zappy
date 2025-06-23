/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pfk.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

eggs_t *create_egg_from_player(player_t *player)
{
    eggs_t *new_egg;

    if (!player || !player->team)
        return NULL;
    new_egg = malloc(sizeof(*new_egg));
    if (!new_egg)
        return NULL;
    new_egg->id = player->team->id * 1000 + rand() % 1000;
    new_egg->creator_id = player->id;
    new_egg->position[0] = player->position[0];
    new_egg->position[1] = player->position[1];
    new_egg->next = player->team->egg;
    player->team->egg = new_egg;
    return new_egg;
}

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
