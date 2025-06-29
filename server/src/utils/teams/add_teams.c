/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** add_teams
*/

/**
 * @file add_teams.c
 * @brief Team management: add a new team to the server.
 *
 * This file contains the logic to dynamically allocate and initialize a new
 * team structure, including its metadata and linked lists for players and
 * eggs.
 * The new team is prepended to the existing team list of the server.
 *
 * @author Noé Carabin
 * @date 2025
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void add_teams(server_t *server, char *name)
{
    teams_t *node = malloc(sizeof(*node));

    if (!node)
        logger(server, "MALLOC", PERROR, true);
    node->name = strdup(name);
    node->id = server->teams_count;
    node->slots_used = 0;
    node->slots_max = server->starter_eggs_number;
    node->win = false;
    node->eliminated = false;
    node->egg = NULL;
    node->player = NULL;
    node->next = server->teams;
    server->teams = node;
    server->teams_count++;
}
