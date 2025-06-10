/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** add_teams
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void add_teams(server_t *server, char *name)
{
    teams_t *node = malloc(sizeof(*node));

    if (!node) {
        perror("[ERROR] - malloc");
        exit(84);
    }
    node->name = strdup(name);
    node->id = server->teams_count;
    node->slots_used = 0;
    node->win = false;
    node->eliminated = false;
    node->egg = NULL;
    node->player = NULL;
    node->next = server->teams;
    server->teams = node;
    server->teams_count++;
}
