/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_right.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_right(server_t *server, int index, const char *args)
{
    switch (server->poll.client_list[index].player->direction) {
        case NORTH:
            server->poll.client_list[index].player->direction = EAST;
            break;
        case EAST:
            server->poll.client_list[index].player->direction = SOUTH;
            break;
        case SOUTH:
            server->poll.client_list[index].player->direction = WEST;
            break;
        case WEST:
            server->poll.client_list[index].player->direction = NORTH;
            break;
        default:
            break;
    }
}
