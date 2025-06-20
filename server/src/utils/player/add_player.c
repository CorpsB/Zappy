/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** add_player
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void free_pos(unsigned int *pos)
{
    if (pos)
        free(pos);
}

void add_player(server_t *server, int index, teams_t *teams)
{
    player_t *node = malloc(sizeof(*node));
    unsigned int *pos = hatching_egg(server, teams);

    if (!node)
        logger(server, "MALLOC", PERROR, true);
    server->poll.client_list[index].player = node;
    node->id = server->player_count;
    node->position[0] = pos[0];
    node->position[1] = pos[1];
    node->lvl = 1;
    node->team = teams;
    node->is_dead = false;
    node->cycle_before_death = 1260;
    node->direction = (rand() % 4) + 1;
    node->socket_fd = server->poll.pollfds[index].fd;
    node->team = teams;
    node->inventory = create_resources();
    node->next = teams->player;
    teams->player = node;
    server->player_count++;
    free_pos(pos);
}
