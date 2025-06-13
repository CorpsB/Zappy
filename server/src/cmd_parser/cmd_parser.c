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

void cmd_parser(server_t *server, int index, char *cmd)
{
    char **args = str_to_array(cmd, ' ');

    for (int i = 0; command_table[i].name != NULL; i++) {
        if (strncmp(cmd, command_table[i].name, strlen(command_table[i].name)) == 0) {
            command_table[i].func(server, index, args);
            return;
        }
    }
    dprintf(server->poll.pollfds[index].fd, "ko\n");
}