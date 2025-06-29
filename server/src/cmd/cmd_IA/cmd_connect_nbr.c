/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_connect_nbr.c
*/

/**
 * @file cmd_connect_nbr.c
 * @brief Handles the "connect_nbr" command to report free slots for a team.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Calculates and sends to the player the number of free connection slots
 * remaining for their team based on the maximum allowed minus used slots.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_connect_nbr(server_t *server, int index, char **args)
{
    player_t *pl;
    teams_t *team;
    int free_slots;
    char *buffer = NULL;

    (void)args;
    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    pl = server->poll.client_list[index].player;
    team = pl->team;
    free_slots = (int)server->starter_eggs_number - team->slots_used;
    if (free_slots < 0)
        free_slots = 0;
    if (asprintf(&buffer, "%d\n", free_slots) == -1)
        logger(server, "ASPRINTF : CONNECT_NBR", PERROR, true);
    send_str(server, pl->socket_fd, buffer, true);
}
