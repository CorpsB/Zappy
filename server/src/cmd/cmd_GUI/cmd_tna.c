/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_tna.c
*/

/**
 * @file cmd_tna.c
 * @brief Implements the "tna" graphical command for the Zappy server.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Handles the "tna" command which lists all team names registered
 * on the server.
 * For each team, the server sends a message:
 * "tna <team_name>"
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_tna(server_t *server, int index, char **args)
{
    int fd;
    teams_t *team;
    char *buffer = NULL;

    (void)args;
    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    fd = server->poll.pollfds[index].fd;
    for (team = server->teams; team; team = team->next) {
        if (!team->name)
            continue;
        if (asprintf(&buffer, "tna %s\n", team->name) == -1)
            logger(server, "ASPRINTF : TNA", PERROR, true);
        send_str(server, fd, buffer, true);
    }
}
