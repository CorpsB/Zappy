/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_sbp
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/cmd.h"
#include "include/cmd_parser_table.h"

void event_sbp(server_t *server, int index, char **args, int i)
{
    dprintf(server->poll.pollfds[index].fd, "sbp\n");
    logger(server, "INVALID ARGS  OR ARGS NUMBER FOR THIS COMMAND",
        INFO, false);
    if (server->debug) {
        printf("CMD : %s\tARGS SIZE : %u\tEXPECTED SIZE : %u\n\n",
            gui_command_table[i].name,
            table_size(args),
            gui_command_table[i].argument_nbr);
        dprintf(server->debug_fd,
            "CMD : %s\t ARGS SIZE : %u\tEXPECTED SIZE : %u\n\n",
            gui_command_table[i].name,
            table_size(args),
            gui_command_table[i].argument_nbr);
    }
}