/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_player
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void see_direction(direction_t dir)
{
    dprintf(2, "  Direction        : ");
    if (dir == NORTH)
        dprintf(2, "NORTH\n");
    if (dir == EAST)
        dprintf(2, "EAST\n");
    if (dir == SOUTH)
        dprintf(2, "SOUTH\n");
    if (dir == WEST)
        dprintf(2, "WEST\n");
}

void see_a_player(player_t *player)
{
    if (!player) {
        dprintf(2, "  [NULL player]\n");
        return;
    }
    dprintf(2, "  ID               : %u\n", player->id);
    dprintf(2, "  Position         : (%u, %u)\n",
        player->position[0], player->position[1]);
    dprintf(2, "  Level            : %u\n", player->lvl);
    dprintf(2, "  Cycles to death  : %u\n", player->cycle_before_death);
    dprintf(2, "  Socket FD        : %d\n", player->socket_fd);
    see_direction(player->direction);
    if (player->team && player->team->name)
        dprintf(2, "  Team name        : %s\n", player->team->name);
    else
        dprintf(2, "  Team name        : (null)\n");
    see_inventory(player->inventory);
}

void see_all_players(player_t *players)
{
    int i = 0;

    dprintf(2, "===== PLAYERS =====\n");
    while (players) {
        dprintf(2, "Player #%d:\n", i);
        see_a_player(players);
        players = players->next;
        i++;
    }
    dprintf(2, "===================\n");
}
