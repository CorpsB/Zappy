/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_plv.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include <ctype.h>

/**
 * @brief Tries to parse a player ID from args and validate it.
 * @param args Argument array (args[1] must be the player ID).
 * @param id_out Pointer to output parsed ID.
 * @return 0 on success, 1 on failure.
*/
static int parse_plv_args(char **args, unsigned int *id_out)
{
    long id;
    char *end;

    if (!args || !args[1])
        return 1;
    id = strtol(args[1], &end, 10);
    while (*end && isspace((unsigned char)*end))
        end++;
    if (*end || id < 0)
        return 1;
    *id_out = (unsigned int)id;
    return 0;
}

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

/**
 * @brief Searches for a player by ID across all teams.
 * @param server The server structure containing teams.
 * @param id The target player ID.
 * @return player_t* if found, NULL otherwise.
*/
static player_t *find_player_by_id(const server_t *server, unsigned int id)
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

void cmd_plv(server_t *server, int index, char **args)
{
    int fd;
    unsigned int id;
    player_t *pl;

    if (!server || check_graphical(server, index) != 0)
        return;
    fd = server->poll.pollfds[index].fd;
    if (parse_plv_args(args, &id) != 0)
        return (void)dprintf(fd, "ko\n");
    pl = find_player_by_id(server, id);
    if (!pl)
        return (void)dprintf(fd, "ko\n");
    dprintf(fd, "plv %u %u\n", pl->id, pl->lvl);
}
