/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_parser
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/cmd.h"
#include "include/cmd_parser_table.h"

static bool is_new_player(server_t *server, int index, char *cmd)
{
    for (teams_t *team = server->teams; team != NULL; team = team->next)
        if (strncmp(cmd, team->name, strlen(team->name)) == 0) {
            cmd_player(server, index, team);
            return true;
        }
    return false;
}

static bool unknown_client(server_t *server, int index, char *cmd)
{
    if (strncmp(cmd, "GRAPHIC", 7) == 0) {
        cmd_graphic(server, index, NULL);
        return true;
    }
    if (is_new_player(server, index, cmd))
        return true;
    return false;
}

void cmd_parser(server_t *server, int index, char *cmd)
{
    char **args = str_to_array(cmd, " ");

    if (server->poll.client_list[index].whoAmI == UNKNOWN) {
        if (!unknown_client(server, index, cmd))
            dprintf(server->poll.pollfds[index].fd, "ko\n");
        free_table(args);
        return;
    }
    for (int i = 0; command_table[i].name != NULL; i++) {
        if (strncmp(cmd, command_table[i].name,
            strlen(command_table[i].name)) == 0) {
            command_table[i].func(server, index, args);
            free_table(args);
            return;
        }
    }
    dprintf(server->poll.pollfds[index].fd, "ko\n");
    free_table(args);
}
