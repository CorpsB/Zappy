/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** add_cmd
*/

/**
 * @file add_cmd.c
 * @brief Handles incoming commands and appends them to player or client
 * buffers.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 *
 * @details
 * This file provides functions to:
 * - Detect whether an incoming command contains a newline (`\n`),
 * - Concatenate multi-part command strings until they are complete,
 * - Dispatch full commands to the command parser,
 * - Distinguish between anonymous clients (e.g., GUI) and players,
 * - Manage command queues for each player (up to 10 commands).
 *
 * This logic ensures that commands received over multiple network
 * chunks are correctly reconstructed before processing.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static bool is_char_inside(char *str, char sp)
{
    if (!str)
        return false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == sp)
            return true;
    }
    return false;
}

static void call_to_parser(server_t *server, char *, int index)
{
    if (server->poll.client_list[index].cmd &&
        is_char_inside(server->poll.client_list[index].cmd, '\n')) {
        cmd_parser(server, index, server->poll.client_list[index].cmd);
        if (server->poll.client_list[index].cmd) {
            free(server->poll.client_list[index].cmd);
            server->poll.client_list[index].cmd = NULL;
        }
        return;
    }
}

static void no_player_cmd(server_t *server, char *cmd, int index)
{
    char *new_cmd = NULL;

    if (server->poll.client_list[index].cmd &&
        !is_char_inside(server->poll.client_list[index].cmd, '\n')) {
            if (asprintf(&new_cmd, "%s%s",
                server->poll.client_list[index].cmd, cmd) == -1)
                logger(server, "ASPRINTF : ADD CMD", PERROR, true);
            if (server->poll.client_list[index].cmd)
                free(server->poll.client_list[index].cmd);
        server->poll.client_list[index].cmd = new_cmd;
    }
    if (!server->poll.client_list[index].cmd)
        server->poll.client_list[index].cmd = strdup(cmd);
    call_to_parser(server, cmd, index);
}

static bool player_cmd(server_t *server, char *cmd, player_t *pl, int k)
{
    char *new_cmd = NULL;

    if (pl->cmd[k] && !is_char_inside(pl->cmd[k], '\n')) {
        if (asprintf(&new_cmd, "%s%s", pl->cmd[k], cmd))
            logger(server, "NEW CMD", PERROR, true);
        if (pl->cmd[k])
            free(pl->cmd[k]);
        pl->cmd[k] = new_cmd;
        return true;
    }
    if (!pl->cmd[k]) {
        pl->cmd[k] = strdup(cmd);
        return true;
    }
    return false;
}

void add_cmd(server_t *server, char *cmd, int index)
{
    player_t *pl;

    if (server->poll.client_list[index].whoAmI != PLAYER)
        return no_player_cmd(server, cmd, index);
    pl = server->poll.client_list[index].player;
    for (int k = 0; k < 10; k++)
        if (player_cmd(server, cmd, pl, k))
            return;
}
