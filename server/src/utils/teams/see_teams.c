/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_teams
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void see_one_team(teams_t *team)
{
    if (!team)
        return;
    printf("\t[TEAM] Name: %s | ID: %d\n", team->name, team->id);
    printf("\t\tSlots used: %d\n", team->slots_used);
    printf("\t\tWin: %s\n", team->win ? "true" : "false");
    printf("\t\tEliminated: %s\n", team->eliminated ? "true" : "false");
    see_all_eggs(team->egg);
    // see_all_players(team->player);
}

void see_teams(teams_t *teams)
{
    printf("[DEBUG] - SEE TEAMS :\n\n");
    for (teams_t *current = teams; current != NULL; current = current->next)
        see_one_team(current);
}
