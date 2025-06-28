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

int load_next_time(server_t *, player_t *pl)
{
    for (int i = 0; player_command_table[i].name != NULL; i++) {
        if (strncmp(pl->cmd[0], player_command_table[i].name,
            strlen(player_command_table[i].name)) == 0) {
            return player_command_table[i].time;
        }
    }
    return 0;
}

static void delete_cmd(server_t *, player_t *pl)
{
    for (int i = 0; i < 10; i++)
        pl->cmd[i] = pl->cmd[i + 1];
    pl->cmd[10] = NULL;
}


void player_cmd_execution(server_t *server)
{
    player_t *pl;

    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI != PLAYER)
            continue;
        pl = server->poll.client_list[i].player;
        if (pl->is_dead || pl->is_freeze)
            continue;
        if (pl->time == 0 && pl->is_waiting && pl->cmd[0] != NULL) {
            cmd_parser(server, i, pl->cmd[0]);
            delete_cmd(server, pl);
            pl->is_waiting = false;
        }
        if (pl->time == 0 && !pl->is_waiting && pl->cmd[0] != NULL) {
            pl->time = load_next_time(server, pl);
            pl->is_waiting = true;
            continue;
        }
        if (pl->time > 0)
        pl->time--;
    }
}
