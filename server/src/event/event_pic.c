/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** event_pic
*/

/**
 * @file event_pic.c
 * @brief Implements the event for player beginning an incantation ("pic").
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "pic" message with player position and level,
 * and appends other players' IDs who are involved and frozen at
 * the same position and level.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/incantation_table.h"

/**
 * @brief Adds a player's ID to an existing message.
 * The function appends " #<player_id>" to the given message and
 * frees the original message.
 * @param server Pointer to the server structure.
 * @param player Pointer to the player whose ID will be added.
 * @param message The message to modify (will be freed inside this function).
 * @return A new allocated string with the player ID added, or NULL
 * on failure.
*/
static char *add_id_on_message(server_t *server, player_t *player,
    char *message)
{
    char *result = NULL;

    if (asprintf(&result, "%s #%u", message, player->id) == -1)
        logger(server, "ASPRINTF : PIC", PERROR, true);
    if (message)
        free(message);
    return result;
}

void event_pic(server_t *server, player_t *player)
{
    char *message = NULL;
    player_t *tmp;

    if (asprintf(&message, "pic %u %u %u #%u", player->position[0],
        player->position[1], player->lvl, player->id) == -1)
        logger(server, "ASPRINTF : PIC", PERROR, true);
    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI != PLAYER)
            continue;
        tmp = server->poll.client_list[i].player;
        if (tmp != player && !tmp->is_dead &&
        tmp->position[0] == player->position[0] &&
        tmp->position[1] == player->position[1] && tmp->is_freeze &&
        tmp->lvl == player->lvl)
            message = add_id_on_message(server, tmp, message);
    }
    send_to_all_gui(server, message);
}
