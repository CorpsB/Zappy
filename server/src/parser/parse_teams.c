/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** parse_teams
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

int parse_teams(char **av, server_t *server, int i)
{
    int j = i + 1;

    for (; av[j] && av[j][0] != '-'; j++)
        add_teams(server, av[j]);
    return j - 1;
}
