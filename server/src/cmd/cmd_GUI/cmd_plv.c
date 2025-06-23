/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_plv.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
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

void cmd_plv(server_t *server, int index, char **args)
{
    int fd;
    unsigned int id;
    player_t *pl;

    if (!server || check_graphical(server, index) != 0)
        return;
    fd = server->poll.pollfds[index].fd;
    if (parse_plv_args(args, &id) != 0)
        return (void)dprintf(fd, "ko\n");
    pl = find_player_by_id(server, id);
    if (!pl)
        return (void)dprintf(fd, "ko\n");
    dprintf(fd, "plv %u %u\n", pl->id, pl->lvl);
}
