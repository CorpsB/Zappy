/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_connect_nbr.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_connect_nbr(server_t *server, int index, char **)
{
    player_t *pl;
    teams_t *team;
    int free_slots;

    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    if (check_autorized(server, index) != 0)
        return;
    pl = server->poll.client_list[index].player;
    team = pl->team;
    free_slots = (int)server->max_connections_per_team - team->slots_used;
    if (free_slots < 0)
        free_slots = 0;
    dprintf(pl->socket_fd, "%d\n", free_slots);
}
