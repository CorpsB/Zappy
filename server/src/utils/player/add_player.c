/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** add_player
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void add_player(server_t *server, int socket, teams_t *teams)
{
    player_t *node = malloc(sizeof(*node));

    if (!node)
        logger(server, "MALLOC", PERROR, true);
    node->id = server->player_count;
    node->position[0] = rand() % server->width;
    node->position[1] = rand() % server->height;
    node->lvl = 1;
    node->cycle_before_death = 1260;
    node->direction = (rand() % 4) + 1;
    node->socket_fd = socket;
    node->team = teams;
    node->inventory = create_resources();
    node->next = teams->player;
    teams->player = node;
    server->player_count++;
}
