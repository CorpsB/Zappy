/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** free_teams
*/

/**
 * @file free_teams.c
 * @brief Functions to free memory used by teams in the server.
 *
 * This file defines utilities to release all dynamically allocated memory
 * associated with teams, including their names, eggs, and players.
 *
 * @author Noé Carabin
 * @date 2025
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Free all resources associated with a single team.
 * Frees the team name string, all associated eggs, all players,
 * then frees the team node itself.
 * @param teams Pointer to the team node to free.
*/
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
