/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_ppo.c
*/

/**
 * @file cmd_ppo.c
 * @brief Implements the "ppo" graphical command for the Zappy server.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * This file handles the "ppo" command, which allows a graphical client
 * to request the position and orientation of a specific player.
 * The server responds with:
 * "ppo <player_id> <x> <y> <direction>"
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/cmd.h"
#include "include/cmd_parser_table.h"
#include <ctype.h>

/**
 * @brief Tries to convert a string to a positive long integer.
 * @param str The input string
 * @param out Pointer to store the result
 * @return int 0 if valid, 1 if invalid
*/
static int parse_ppo_id(const char *str, long *out)
{
    char *end;
    long val;

    if (!str)
        return 1;
    val = strtol(str, &end, 10);
    while (*end && isspace((unsigned char)*end))
        end++;
    if (*end || val < 0)
        return 1;
    *out = val;
    return 0;
}

static int find_gui_command_index(const char *name)
{
    for (int i = 0; gui_command_table[i].name; i++) {
        if (strcmp(gui_command_table[i].name, name) == 0)
            return i;
    }
    return -1;
}

void cmd_ppo(server_t *server, int index, char **args)
{
    int fd;
    long id;
    player_t *target;
    int i = find_gui_command_index("ppo");
    char *buffer = NULL;

    if (!server || !args || !args[1])
            return event_sbp(server, index, args, i);
    fd = server->poll.pollfds[index].fd;
    if (parse_ppo_id(args[1], &id) != 0)
        return event_sbp(server, index, args, i);
    target = find_player_by_id(server, (unsigned int)id);
    if (!target)
        return event_sbp(server, index, args, i);
    if (asprintf(&buffer, "ppo %d %d %d %d\n", target->id,
        target->position[0], target->position[1], target->direction) == -1)
        logger(server, "ASPRINTF : PPO", PERROR, true);
    send_str(server, fd, buffer, true);
}
