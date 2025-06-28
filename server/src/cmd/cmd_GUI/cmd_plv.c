/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_plv.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/cmd.h"
#include "include/cmd_parser_table.h"
#include <ctype.h>

/**
 * @brief Tries to parse a player ID from args and validate it.
 * @param args Argument array (args[1] must be the player ID).
 * @param id_out Pointer to output parsed ID.
 * @return 0 on success, 1 on failure.
*/
static int parse_plv_args(char **args, unsigned int *id_out)
{
    long id;
    char *end;

    if (!args || !args[1])
        return 1;
    id = strtol(args[1], &end, 10);
    while (*end && isspace((unsigned char)*end))
        end++;
    if (*end || id < 0)
        return 1;
    *id_out = (unsigned int)id;
    return 0;
}

static int find_gui_command_index(const char *name)
{
    for (int i = 0; gui_command_table[i].name; i++) {
        if (strcmp(gui_command_table[i].name, name) == 0)
            return i;
    }
    return -1;
}

void cmd_plv(server_t *server, int index, char **args)
{
    int fd;
    unsigned int id;
    player_t *pl;
    int i = find_gui_command_index("plv");
    char *buffer = NULL;

    if (!server)
        return;
    fd = server->poll.pollfds[index].fd;
    if (parse_plv_args(args, &id) != 0)
        return event_sbp(server, index, args, i);
    pl = find_player_by_id(server, id);
    if (!pl)
        return event_sbp(server, index, args, i);
    if (asprintf(&buffer, "plv %u %u\n", pl->id, pl->lvl) == -1)
        logger(server, "ASPRINTF : PLV", PERROR, true);
    send_str(server, fd, buffer);
}
