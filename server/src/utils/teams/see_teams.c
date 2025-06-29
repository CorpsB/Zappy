/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_teams
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void see_one_team(server_t *server, teams_t *team, int fd)
{
    if (!team)
        return;
    dprintf(fd, "\n[TEAM] Name: %s | ID: %d\n", team->name, team->id);
    dprintf(fd, "\tSlots used: %d\n", team->slots_used);
    dprintf(fd, "\tWin: %s\n", team->win ? "true" : "false");
    dprintf(fd, "\tEliminated: %s\n", team->eliminated ? "true" : "false");
    see_all_eggs(server, team->egg, fd);
    see_all_players(server, team->player, fd);
}

void see_teams(server_t *server, teams_t *teams, int fd)
{
    dprintf(fd, "====== TEAMS LIST ======\n");
    for (teams_t *current = teams; current != NULL; current = current->next)
        see_one_team(server, current, fd);
    dprintf(fd, "\n======= END =======\n");
}
