/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_incantation.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/incantation_table.h"

/**
 * @brief Check if two players are on the same position.
 * @param first First player.
 * @param second Second player.
 * @return true if positions are identical, false otherwise.
*/
static bool is_same_pos(player_t *first, player_t *second)
{
    if (first->position[0] == second->position[0] &&
    first->position[1] == second->position[1])
        return true;
    return false;
}

/**
 * @brief Count the number of players on the same tile with the same level.
 * If a frozen player is already on the tile, returns -1 to indicate
 * an ongoing incantation.
 * @param server The server structure.
 * @param pl The reference player.
 * @return The number of matching players, or -1 if an incantation is active.
*/
static unsigned int found_player_on_tile(server_t *server, player_t *pl)
{
    unsigned int count = 0;
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

/**
 * @brief Check if all conditions for an incantation are met.
 * Verifies required resources on the tile and the number of players.
 * @param server The server structure.
 * @param pl The player attempting the incantation.
 * @return true if all conditions are satisfied, false otherwise.
*/
static bool check_condition(server_t *server, player_t *pl)
{
    resources_t map = server->map[pl->position[1]][pl->position[0]];

    if (pl->lvl >= 8)
        return false;
    if (found_player_on_tile(server, pl) < requirement[pl->lvl -1].lvl ||
        map.linemate < requirement[pl->lvl -1].linemate ||
        map.deraumere < requirement[pl->lvl -1].deraumere ||
        map.sibur < requirement[pl->lvl -1].sibur ||
        map.mendiane < requirement[pl->lvl -1].mendiane ||
        map.phiras < requirement[pl->lvl -1].phiras ||
        map.thystame < requirement[pl->lvl -1].thystame)
        return false;
    return true;
}

bool start_incantation(server_t *server, player_t *pl)
{
    player_t *tmp;

    if (!check_condition(server, pl)) {
        send_str(server, pl->socket_fd, "ko\n", false);
        return false;
    }
    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI != PLAYER)
            continue;
        tmp = server->poll.client_list[i].player;
        if (!tmp->is_dead && tmp->lvl == pl->lvl && is_same_pos(tmp, pl)) {
            tmp->is_freeze = true;
            send_str(server, tmp->socket_fd, "Elevation underway\n", false);
        }
    }
    event_pic(server, pl);
    return true;
}

/**
 * @brief Handle an incantation failure.
 * Unfreezes involved players and notifies them of the failure.
 * @param server The server structure.
 * @param index The index of the player in the poll list.
*/
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
            send_str(server, tmp->socket_fd, "ko\n", false);
        }
    }
    event_pie(server, pl, false);
}

/**
 * @brief Remove resources from the tile after a successful incantation.
 * @param server The server structure.
 * @param index The index of the player in the poll list.
*/
static void delete_stuff(server_t *server, int index)
{
    player_t *pl = server->poll.client_list[index].player;
    resources_t map = server->map[pl->position[1]][pl->position[0]];

    map.deraumere -= requirement[pl->lvl - 1].deraumere;
    map.linemate -= requirement[pl->lvl - 1].linemate;
    map.mendiane -= requirement[pl->lvl - 1].mendiane;
    map.phiras -= requirement[pl->lvl - 1].phiras;
    map.sibur -= requirement[pl->lvl - 1].sibur;
    map.thystame -= requirement[pl->lvl - 1].thystame;
}

static void notify_success(server_t *server, player_t *player)
{
    char *buffer = NULL;

    player->lvl++;
    player->is_freeze = false;
    event_plv(server, player);
    if (asprintf(&buffer, "Current level: %u\n", player->lvl) == -1)
        logger(server, "ASPRINTF : INCANTATION", PERROR, true);
    send_str(server, player->socket_fd, buffer, true);
}

static void upgrade_players_on_tile(server_t *server, player_t *pl)
{
    player_t *tmp;

    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI != PLAYER)
            continue;
        tmp = server->poll.client_list[i].player;
        if (tmp->lvl == pl->lvl && is_same_pos(tmp, pl) && !tmp->is_dead)
            notify_success(server, tmp);
    }
}

/**
 * @brief Finalize an incantation attempt.
 * Checks conditions again, applies consequences, and levels up players.
 * @param server The server structure.
 * @param index The index of the player in the poll list.
 * @param args Unused parameter (command arguments).
*/
static void end_incantation(server_t *server, int index, char **)
{
    player_t *pl = server->poll.client_list[index].player;

    if (!check_condition(server, pl))
        return elevation_failed(server, index);
    delete_stuff(server, index);
    upgrade_players_on_tile(server, pl);
    event_pie(server, pl, true);
}

void cmd_incantation(server_t *server, int index, char **args)
{
    end_incantation(server, index, args);
}
