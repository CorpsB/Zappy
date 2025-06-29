/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cdm_bct.c
*/

/**
 * @file cmd_bct.c
 * @brief Implements the "bct" graphical command for the Zappy server.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * This file contains the logic for handling the "bct" command, which
 * allows graphical clients to query the resources present at a specific
 * tile on the game map.
 * The coordinates provided by the client are parsed and validated before
 * sending a response formatted according to the protocol:
 * "bct <y> <x> <food> <linemate> <deraumere> <sibur> <mendiane>
 * <phiras> <thystame>"
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/cmd.h"
#include "include/cmd_parser_table.h"
#include <ctype.h>

/**
 * @brief Convert a single @p token to an integer coordinate and
 *        check it is within [0, max-1].
 *
 * @param token C-string to convert (must not be NULL).
 * @param max   Exclusive upper bound (map width or height).
 * @param out   [out] Receives the validated value.
 *
 * @retval 0 Success.
 * @retval 1 Failure (NULL token, non-numeric chars, or out of range).
*/
static int parse_coord(const char *token, long max, long *out)
{
    long v;
    char *end;

    if (!token)
        return 1;
    v = strtol(token, &end, 10);
    while (*end && isspace((unsigned char)*end))
        ++end;
    if (*end || v < 0 || v >= max)
        return 1;
    *out = v;
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

/**
 * @brief Extract X and Y from the "bct" argument list and verify they
 *        lie inside the current map.
 *
 * Expected layout of @p args (output of str_to_array):
 *   args[0] = "bct", args[1] = x, args[2] = y, args[3] = NULL.
 *
 * @retval 0 Success – coordinates copied to @p x_out / @p y_out.
 * @retval 1 Failure – missing token or invalid/out-of-range value.
*/
static int parse_bct_coords(char **args, const server_t *server,
    int *x_out, int *y_out)
{
    long x;
    long y;
    int x_valid = 0;
    int y_valid = 0;

    if (!args || !args[1] || !args[2])
        return 1;
    x_valid = (parse_coord(args[1], (long)server->width, &x) == 0);
    y_valid = (parse_coord(args[2], (long)server->height, &y) == 0);
    if (x_valid && y_valid) {
        *x_out = (int)x;
        *y_out = (int)y;
        return 0;
    }
    return 1;
}

void cmd_bct(server_t *server, int index, char **args)
{
    int x = 0;
    int y = 0;
    int fd;
    int i = find_gui_command_index("bct");
    char *buffer = NULL;
    const resources_t *t;

    if (!server || !args || !args[1] || !args[2])
        return event_sbp(server, index, args, i);
    fd = server->poll.pollfds[index].fd;
    if (parse_bct_coords(args, server, &x, &y) != 0) {
        x = 0;
        y = 0;
    }
    t = &server->map[y][x];
    if (asprintf(&buffer, "bct %d %d %u %u %u %u %u %u %u\n", y, x,
        t->food, t->linemate, t->deraumere, t->sibur,
        t->mendiane, t->phiras, t->thystame) == -1)
        logger(server, "ASPRINTF : BCT", PERROR, true);
    send_str(server, fd, buffer, true);
}
