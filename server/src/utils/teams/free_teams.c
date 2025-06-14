/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** free_teams
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void free_a_team(teams_t *teams)
{
    if (!teams)
        return;
    if (teams->name)
        free(teams->name);
    free_all_egs(teams->egg);
    free_all_player(teams->player);
    free(teams);
}

void free_all_teams(teams_t *teams)
{
    teams_t *tmp;

    while (teams) {
        tmp = teams->next;
        free_a_team(teams);
        teams = tmp;
    }
}
