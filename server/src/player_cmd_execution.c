/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** player_cmd_execution
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void load_cmd(server_t *server, player_t *pl, int i)
{
    if (pl->cmd[0] == NULL)
        return;
    cmd_parser(server, i, pl->cmd[0]);
    for (int j = 0; j < 10; j++) {
        pl->cmd[j] = pl->cmd[j + 1];
    }
    pl->cmd[10] = NULL;
}

void player_cmd_execution(server_t *server)
{
    player_t *pl;

    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI != PLAYER ||
            server->poll.client_list->player->is_dead)
            continue;
        pl = server->poll.client_list[i].player;
        if (pl->time == 0) {
            load_cmd(server, pl, i);
            continue;
        }
        pl->time--;
    }
}
