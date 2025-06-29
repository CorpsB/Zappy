/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** add_eggs.c
*/

/**
 * @file add_eggs.c
 * @brief Implements egg creation logic for both starter and player-laid eggs.
 * @author Noé Carabin (CorpsB)
 * @version 1.0
 * @date 2025-06
 * @details
 * Provides functions to allocate and initialize egg structures associated
 * with a team. `generate_starter_eggs` randomly places eggs on the map at
 * startup with no creator, while `add_eggs` is used during gameplay when
 * a player lays an egg at a specific position. Eggs are added to the team's
 * linked list and tracked using a global egg ID counter.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void generate_starter_eggs(server_t *server, teams_t *teams)
{
    eggs_t *node = malloc(sizeof(*node));

    if (!node)
        logger(server, "MALLOC", PERROR, true);
    node->id = server->eggs_count;
    node->position[0] = rand() % server->width;
    node->position[1] = rand() % server->height;
    node->creator_id = -1;
    node->next = teams->egg;
    teams->egg = node;
    server->eggs_count++;
}

void add_eggs(server_t *server, unsigned int creator_id, teams_t *teams,
    int *pos)
{
    eggs_t *node = malloc(sizeof(*node));

    if (!node)
        logger(server, "MALLOC", PERROR, true);
    node->id = server->eggs_count;
    node->position[0] = pos[0];
    node->position[1] = pos[1];
    node->creator_id = creator_id;
    node->next = teams->egg;
    teams->egg = node;
    server->eggs_count++;
}
