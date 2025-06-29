/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_fork.c
*/

/**
 * @file cmd_fork.c
 * @brief Handles the "fork" command to spawn new eggs for the player's team.
 * @author Noé Carain
 * @version 1.0
 * @date 2025-06
 * @details
 * Increases the maximum slots of the player's team, creates an egg at
 * the player's
 * position, and sends an acknowledgment to the player.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_fork(server_t *server, int index, char **args)
{
    player_t *pl;

    (void)args;
    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    pl = server->poll.client_list[index].player;
    pl->team->slots_max++;
    add_eggs(server, pl->id, pl->team, (int *)pl->position);
    send_str(server, pl->socket_fd, "ok\n", false);
    event_pfk(server, pl);
}
