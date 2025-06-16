/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_player
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

//WARNING : This command is special. Don't put them on the cmd table.
void cmd_player(server_t *server, int index, teams_t *teams)
{
    if (server->poll.client_list[index].whoAmI == UNKNOWN &&
        teams->slots_used < server->max_connections_per_team) {
        server->poll.client_list[index].whoAmI = PLAYER;
        add_player(server, server->poll.pollfds[index].fd, teams);
        dprintf(server->poll.pollfds[index].fd, "ok\n");
    } else {
        dprintf(server->poll.pollfds[index].fd, "ko\n");
    }
}
