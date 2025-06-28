/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** free_player
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
