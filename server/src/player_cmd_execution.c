/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** player_cmd_execution
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/cmd.h"
#include "include/cmd_parser_table.h"


static void load_next_time(server_t *, player_t *pl, char *cmd)
{
    for (int i = 0; player_command_table[i].name != NULL; i++) {
        if (strncmp(cmd, player_command_table[i].name,
            strlen(player_command_table[i].name)) == 0) {
            pl->time = player_command_table[i].time;
            return;
        }
    }
}

static void load_cmd(server_t *server, player_t *pl, int i)
{
    if (pl->cmd[0] == NULL)
        return;
    cmd_parser(server, i, pl->cmd[0]);
    for (int j = 0; j < 10; j++) {
        pl->cmd[j] = pl->cmd[j + 1];
    }
    if (pl->cmd[0] != NULL)
        load_next_time(server, pl, pl->cmd[0]);
    pl->cmd[10] = NULL;
}

void player_cmd_execution(server_t *server)
{
    player_t *pl;

    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI != PLAYER)
            continue;
        pl = server->poll.client_list[i].player;
        if (pl->is_dead)
            continue;
        if (pl->time == 0) {
            load_cmd(server, pl, i);
            continue;
        }
        pl->time--;
    }
}
