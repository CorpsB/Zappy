/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_incantation.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "incantation_table.h"

static int found_player_on_tile(server_t *server, int index)
{
    int count = 0;
    player_t *pl = server->poll.client_list[index].player;
    player_t *tmp;

    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI != PLAYER)
            continue;
        tmp = server->poll.client_list[i].player;
        if (!tmp->is_dead && tmp->is_freeze && is_same_pos(pl, tmp))
            return -1;
        if (tmp->lvl == pl->lvl && !tmp->is_dead && is_same_pos(pl, tmp))
            count++;
    }
    return count;
}

static bool check_condition(server_t *server, int index)
{
    player_t *pl = server->poll.client_list[index].player;
    resources_t map = server->map[pl->position[0]][pl->position[1]];

    if (pl->lvl >= 8)
        return false;
    if (found_player_on_tile(server, index) < requirement[pl->lvl -1].lvl ||
        map.linemate < requirement[pl->lvl -1].linemate ||
        map.deraumere < requirement[pl->lvl -1].deraumere ||
        map.sibur < requirement[pl->lvl -1].sibur ||
        map.mendiane < requirement[pl->lvl -1].mendiane ||
        map.phiras < requirement[pl->lvl -1].phiras ||
        map.thystame < requirement[pl->lvl -1].thystame)
        return false;
    return true;
}

static bool is_same_pos(player_t *first, player_t *second)
{
    if (first->position[0] == second->position[0] &&
    first->position[1] == second->position[1])
        return true;
    return false;
}

static void start_incantation(server_t *server, int index, char **args)
{
    player_t *pl = server->poll.client_list[index].player;
    player_t *tmp;

    if (!check_condition(server, index)) {
        drpintf(pl, "ko\n");
        return;
    }
    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI != PLAYER)
            continue;
        tmp = server->poll.client_list[i].player;
        if (!tmp->is_dead && tmp->lvl == pl->lvl && is_same_pos(tmp, pl)) {
            tmp->is_freeze = true;
            dprintf(tmp->socket_fd, "Elevation underway\n");
        }
    }
}

static void elevation_failed(server_t *server, int index)
{
    player_t *pl = server->poll.client_list[index].player;
    player_t *tmp;

    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI != PLAYER)
            continue;
        tmp = server->poll.client_list[i].player;
        if (tmp->lvl == pl->lvl && is_same_pos(tmp, pl) && !tmp->is_dead
            && tmp->is_freeze) {
            tmp->is_freeze = false;
            dprintf(tmp->socket_fd, "ko\n");
        }
    }
}

static void delete_stuff(server_t *server, int index)
{
    player_t *pl = server->poll.client_list[index].player;
    resources_t map = server->map[pl->position[0]][pl->position[1]];

    map.deraumere -= requirement[pl->lvl - 1].deraumere;
    map.linemate -= requirement[pl->lvl - 1].linemate;
    map.mendiane -= requirement[pl->lvl - 1].mendiane;
    map.phiras -= requirement[pl->lvl - 1].phiras;
    map.sibur -= requirement[pl->lvl - 1].sibur;
    map.thystame -= requirement[pl->lvl - 1].thystame;
}

static void end_incantation(server_t *server, int index, char **args)
{
    player_t *pl = server->poll.client_list[index].player;
    player_t *tmp;

    if (!check_condition(server, index)) {
        elevation_failed(server, index);
        return;
    }
    delete_stuff(server, index);
    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI != PLAYER)
            continue;
        tmp = server->poll.client_list[i].player;
        if (tmp->lvl == pl->lvl && is_same_pos(tmp, pl) && !tmp->is_dead) {
            tmp->lvl++;
            tmp->is_freeze = false;
            dprintf(tmp->socket_fd, "Current level: %u\n", tmp->lvl);
        }
    }
}

//Don't forget : Event plz at the end of the lvl up;
void cmd_incantation(server_t *server, int index, const char *args)
{
    return;
}
