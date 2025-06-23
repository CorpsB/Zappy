/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_ppo.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include <ctype.h>

/**
 * @brief Tries to convert a string to a positive long integer.
 * @param str The input string
 * @param out Pointer to store the result
 * @return int 0 if valid, 1 if invalid
*/
static int parse_ppo_id(const char *str, long *out)
{
    char *end;
    long val;

    if (!str)
        return 1;
    val = strtol(str, &end, 10);
    while (*end && isspace((unsigned char)*end))
        end++;
    if (*end || val < 0)
        return 1;
    *out = val;
    return 0;
}

void cmd_ppo(server_t *server, int index, char **args)
{
    int fd;
    long id;
    player_t *target;

    if (!server || !args || !args[1] || check_graphical(server, index) != 0) {
        if (server && args && !args[1])
            dprintf(server->poll.pollfds[index].fd, "ko\n");
        return;
    }
    fd = server->poll.pollfds[index].fd;
    if (parse_ppo_id(args[1], &id) != 0)
        return (void)dprintf(fd, "ko\n");
    target = find_player_by_id(server, (unsigned int)id);
    if (!target)
        return (void)dprintf(fd, "ko\n");
    dprintf(fd, "ppo %d %d %d %d\n", target->id,
        target->position[0], target->position[1], target->direction);
}
