/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_player
*/

/**
 * @file see_player.c
 * @brief Functions to inspect and print player information for debugging.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 *
 * @details
 * This file defines helper functions to display details about players,
 * primarily for debugging or server-side inspection.
 *
 * Functions include:
 * - `see_direction()` – Prints the player's facing direction.
 * - `see_a_player()` – Prints all details of a single player.
 * - `see_all_players()` – Iterates through a team and prints each player.
 *
 * These outputs are intended for use with file descriptors (e.g., sockets,
 * logs, or STDOUT), and integrate with the server's logging/debugging system.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Print the textual representation of a direction to a
 * file descriptor.
 * @param dir Direction enum value (NORTH, EAST, SOUTH, WEST).
 * @param fd File descriptor where the direction string will be printed.
*/
void see_direction(direction_t dir, int fd)
{
    dprintf(fd, "  Direction        : ");
    if (dir == NORTH)
        dprintf(fd, "NORTH\n");
    if (dir == EAST)
        dprintf(fd, "EAST\n");
    if (dir == SOUTH)
        dprintf(fd, "SOUTH\n");
    if (dir == WEST)
        dprintf(fd, "WEST\n");
}

/**
 * @brief Print detailed information about a single player
 * to a file descriptor.
 * Includes ID, position, level, death timer, socket FD, direction,
 * team name,
 * and inventory content.
 * @param player Pointer to the player to print.
 * @param fd File descriptor where output will be printed.
*/
void see_a_player(server_t *server, player_t *player, int fd)
{
    if (!player) {
        dprintf(fd, "  [NULL player]\n");
        return;
    }
    dprintf(fd, "  ID               : %u\n", player->id);
    dprintf(fd, "  Position         : (%u, %u)\n",
        player->position[0], player->position[1]);
    dprintf(fd, "  Level            : %u\n", player->lvl);
    dprintf(fd, "  Cycles to death  : %u\n", player->cycle_before_death);
    dprintf(fd, "  Socket FD        : %d\n", player->socket_fd);
    see_direction(player->direction, fd);
    if (player->team && player->team->name)
        dprintf(fd, "  Team name        : %s\n", player->team->name);
    else
        dprintf(fd, "  Team name        : (null)\n");
    see_inventory(server, player->inventory, fd);
}

void see_all_players(server_t *server, player_t *players, int fd)
{
    int i = 0;

    dprintf(fd, "[PLAYER IN THE TEAM]\n");
    if (!players) {
        dprintf(fd, "\t[NO PLAYERS]\n");
        return;
    }
    while (players) {
        dprintf(fd, "Player #%d:\n", i);
        see_a_player(server, players, fd);
        players = players->next;
        i++;
    }
    dprintf(fd, "\n===================\n");
}
