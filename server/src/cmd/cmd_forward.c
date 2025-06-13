/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_salut.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

    //position[0] = x droite gauche
    //positon[1] = y haut bas

void cmd_forward(server_t *server, int index, const char *args)
{
    player_t *pl;

    if (server->poll.client_list[index].player->direction == NORTH)
    server->poll.client_list[index].player->position[1] =
        (server->poll.client_list[index].player->position[1] + 1)
            % server->height;
    if (server->poll.client_list[index].player->direction == SOUTH)
        server->poll.client_list[index].player->position[1] =
            (server->poll.client_list[index].player->position[1]
                + server->height - 1) % server->height;
    if (server->poll.client_list[index].player->direction == EAST)
        server->poll.client_list[index].player->position[0] =
            (server->poll.client_list[index].player->position[0] + 1)
                % server->width;
    if (server->poll.client_list[index].player->direction == WEST)
        server->poll.client_list[index].player->position[0] =
            (server->poll.client_list[index].player->position[0]
                + server->width - 1) % server->width;
    dprintf(pl->socket_fd, "ok\n");
}
