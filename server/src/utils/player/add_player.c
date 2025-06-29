/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** add_player
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Frees a dynamically allocated position array and increments
 * player count.
 * @param pos Pointer to an array of unsigned int representing
 * position coordinates.
 * @param server Pointer to the server structure to update player count.
*/
static void free_pos(unsigned int *pos, server_t *server)
{
    if (pos)
        free(pos);
    server->player_count++;
}

/**
 * @brief Initialize or reset certain fields of a player node.
 * Sets the player's level to 1, resets command pointers to NULL,
 * initializes inventory food to 10, and marks player as not waiting.
 * @param node Pointer to the player node to complete.
*/
static void complete_node(player_t *node)
{
    node->lvl = 1;
    node->time = 0;
    node->cmd[0] = NULL;
    node->cmd[1] = NULL;
    node->cmd[2] = NULL;
    node->cmd[3] = NULL;
    node->cmd[4] = NULL;
    node->cmd[5] = NULL;
    node->cmd[6] = NULL;
    node->cmd[7] = NULL;
    node->cmd[8] = NULL;
    node->cmd[9] = NULL;
    node->cmd[10] = NULL;
    node->inventory.food = 10;
    node->is_waiting = false;
}

/**
 * @brief Allocate and initialize a new player node.
 * Allocates memory for a player, assigns ID, position, direction, team,
 * socket file descriptor, and initializes inventory and state.
 * @param server Pointer to the server structure.
 * @param index Index in the poll file descriptor array.
 * @param teams Pointer to the team structure the player belongs to.
 * @param pos Pointer to position array (x,y) where the player spawns.
 * @return player_t* Pointer to the initialized player node.
*/
static player_t *init_player_node(server_t *server, int index,
    teams_t *teams, unsigned int *pos)
{
    player_t *node = malloc(sizeof(*node));

    if (!node)
        logger(server, "MALLOC", PERROR, true);
    node->id = server->player_count;
    node->position[0] = pos[0];
    node->position[1] = pos[1];
    node->is_freeze = false;
    node->team = teams;
    node->is_dead = false;
    node->cycle_before_death = 0;
    node->direction = (rand() % 4) + 1;
    node->socket_fd = server->poll.pollfds[index].fd;
    node->inventory = create_resources();
    complete_node(node);
    node->next = teams->player;
    return node;
}

void add_player(server_t *server, int index, teams_t *teams)
{
    unsigned int *pos = hatching_egg(server, teams);
    player_t *node = init_player_node(server, index, teams, pos);

    server->poll.client_list[index].player = node;
    teams->player = node;
    event_pnw(server, node);
    free_pos(pos, server);
}
