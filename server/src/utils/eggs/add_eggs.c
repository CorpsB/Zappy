/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** add_eggs.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void add_eggs(server_t *server, unsigned int creator_id, teams_t *teams)
{
    eggs_t *node = malloc(sizeof(*node));

    if (!node) {
        perror("[ERROR] - malloc");
        exit(84);
    }
    node->id = server->eggs_count;
    node->position[0] = rand() % server->width; //=> A changer
    node->position[1] = rand() % server->height; //=> A changer
    node->creator_id = creator_id;
    node->next = teams->egg;
    teams->egg = node;
    server->eggs_count++;
}
