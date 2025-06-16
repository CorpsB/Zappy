/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_teams
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void see_one_team(teams_t *team, int fd)
{
    if (!team)
        return;
    dprintf(fd, "\t[TEAM] Name: %s | ID: %d\n", team->name, team->id);
    dprintf(fd, "\t\tSlots used: %d\n", team->slots_used);
    dprintf(fd, "\t\tWin: %s\n", team->win ? "true" : "false");
    dprintf(fd, "\t\tEliminated: %s\n", team->eliminated ? "true" : "false");
    see_all_eggs(team->egg, fd);
    see_all_players(team->player, fd);
}

void see_teams(teams_t *teams, int fd)
{
    dprintf(fd, "[DEBUG] - SEE TEAMS :\n\n");
    for (teams_t *current = teams; current != NULL; current = current->next)
        see_one_team(current, fd);
    dprintf(fd, "===== END =====\n");
}
