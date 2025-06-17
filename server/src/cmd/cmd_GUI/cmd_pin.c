/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_pin.c
*/

#include "include/include.h"
#include "include/structure.h"
#include "include/function.h"
#include <ctype.h>

/**
 * @brief Sends inventory of a player to GUI.
 */
static void send_pin(int fd, const player_t *p)
{
    dprintf(fd, "pin %u %u %u %u %u %u %u %u %u %u\n",
        p->id, p->position[0], p->position[1],
        p->inventory.food, p->inventory.linemate,
        p->inventory.deraumere, p->inventory.sibur,
        p->inventory.mendiane, p->inventory.phiras,
        p->inventory.thystame);
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

void cmd_pin(server_t *server, int index, char **args)
{
    int fd;
    long id;
    char *e;
    player_t *p;

    fd = server->poll.pollfds[index].fd;
    if (!args || !args[1] || check_graphical(server, index))
        return (void)dprintf(fd, "ko\n");
    id = strtol(args[1], &e, 10);
    while (*e && isspace((unsigned char)*e))
        e++;
    if (*e || id < 0)
        return (void)dprintf(fd, "ko\n");
    p = find_player_by_id(server, (unsigned int)id);
    if (!p)
        return (void)dprintf(fd, "ko\n");
    send_pin(fd, p);
}
