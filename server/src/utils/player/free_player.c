/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** free_player
*/

/**
 * @file free_player.c
 * @brief Functions to properly free player-related memory in the Zappy server.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 *
 * @details
 * This file contains functions to release the memory allocated for players:
 * - `free_a_player()` frees a single player node, including all pending
 * commands.
 * - `free_all_player()` traverses a linked list of players and frees each one.
 *
 * These functions ensure clean deallocation of player resources to prevent
 * memory leaks when players disconnect or when the server shuts down.
 */


#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Free the memory allocated for a single player node.
 * @param player Pointer to the player node to free.
*/
void free_a_player(player_t *player)
{
    for (int i = 0; i < 11; i++)
        if (player->cmd[i])
            free(player->cmd[i]);
    if (player)
        free(player);
}

void free_all_player(player_t *player)
{
    player_t *tmp;

    while (player) {
        tmp = player->next;
        free_a_player(player);
        player = tmp;
    }
}
