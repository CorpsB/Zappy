/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** search_player
*/

#include "include/include.h"
#include "include/structure.h"
#include "include/function.h"

/**
 * @brief Searches for a player with the given ID in a single team.
 * @param team The team to search in.
 * @param id The target player ID.
 * @return player_t* if found, NULL otherwise.
*/
static player_t *find_in_team(const teams_t *team, unsigned int id)
{
    player_t *pl;

    pl = team->player;
    while (pl) {
        if (pl->id == id)
            return pl;
        pl = pl->next;
    }
    return NULL;
}

player_t *find_player_by_id(const server_t *server, unsigned int id)
{
    teams_t *team;
    player_t *pl;

    team = server->teams;
    pl = NULL;
    while (team && !pl) {
        pl = find_in_team(team, id);
        team = team->next;
    }
    return pl;
}