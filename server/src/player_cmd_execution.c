/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** player_cmd_execution
*/

/**
 * @file player_cmd_execution.c
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06-29
 * @brief Handles the execution of player commands in the Zappy server.
 *
 * This module manages the command queue of each player. It tracks the time
 * required to execute commands, handles waiting states, and invokes the
 * command parser once a command is ready to be executed.
 *
 * Key responsibilities:
 * - Decrement player command timers.
 * - Detect when a command can be executed and process it.
 * - Handle special cases like Incantation which needs pre-checks.
 * - Maintain the FIFO order of the command queue per player.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/cmd.h"
#include "include/cmd_parser_table.h"

/**
 * @brief Remove the first command from the player's command queue.
 * @param server Pointer to the server structure.
 * @param pl Pointer to the player structure.
*/
static void delete_cmd(server_t *, player_t *pl)
{
    for (int i = 0; i < 10; i++)
        pl->cmd[i] = pl->cmd[i + 1];
    pl->cmd[10] = NULL;
}

/**
 * @brief Load the time required to execute the next player command.
 * @param server Pointer to the server structure.
 * @param pl Pointer to the player structure.
 * @return Time in ticks required for the command, or 0 if no valid command.
*/
int load_next_time(server_t *server, player_t *pl)
{
    if (strncmp(pl->cmd[0], "Incantation", 11) == 0) {
        if (start_incantation(server, pl))
            return 300;
        pl->is_waiting = false;
        delete_cmd(server, pl);
        return 0;
    }
    for (int i = 0; player_command_table[i].name != NULL; i++) {
        if (strncmp(pl->cmd[0], player_command_table[i].name,
            strlen(player_command_table[i].name)) == 0) {
            return player_command_table[i].time;
        }
    }
    return 0;
}

static bool loop(server_t *server, player_t **pl, int i)
{
    if (server->poll.client_list[i].whoAmI != PLAYER)
        return true;
    *pl = server->poll.client_list[i].player;
    if ((*pl)->is_dead)
        return true;
    (*pl)->time = (*pl)->time > 0 ? (*pl)->time - 1 : (*pl)->time;
    if ((*pl)->is_freeze) {
        if ((*pl)->is_waiting && (*pl)->time == 0) {
            cmd_parser(server, i, (*pl)->cmd[0]);
            delete_cmd(server, (*pl));
            (*pl)->is_waiting = false;
        }
        return true;
    }
    if ((*pl)->time == 0 && (*pl)->is_waiting && (*pl)->cmd[0] != NULL) {
        cmd_parser(server, i, (*pl)->cmd[0]);
        delete_cmd(server, (*pl));
        (*pl)->is_waiting = false;
    }
    return false;
}

void player_cmd_execution(server_t *server)
{
    player_t *pl = NULL;

    for (int i = 0; i < server->poll.connected_client; i++) {
        pl = NULL;
        if (loop(server, &pl, i))
            continue;
        if (pl && pl->time == 0 && !pl->is_waiting && pl->cmd[0] != NULL) {
            pl->time = load_next_time(server, pl);
            pl->is_waiting = true;
            continue;
        }
    }
}
