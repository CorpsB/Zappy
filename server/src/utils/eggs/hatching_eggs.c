/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** hatching_eggs
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

unsigned int *hatching_egg(server_t *server, teams_t *teams)
{
    unsigned int *pos = malloc(sizeof(int) * 2);
    int random_egg = rand() % eggs_size(teams->egg);
    eggs_t *hatching_egg = teams->egg;

    if (!pos)
        logger(server, "MALLOC", PERROR, true);
    for (int i = 1; i < random_egg; i++)
        hatching_egg = hatching_egg->next;
    pos[0] = hatching_egg->position[0];
    pos[1] = hatching_egg->position[1];
    printf("Coucou les zoulous\n");
    del_egg(server, teams, hatching_egg);
    printf("Coucou les zoulous\n");
    return pos;
}