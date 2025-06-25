/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cdm_bct.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
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
static int parse_bct_coords(char **args,
    const server_t *server, int *x_out, int *y_out)
{
    long x;
    long y;

    if (!args || !args[1] || !args[2])
        return 1;
    if (parse_coord(args[1], (long)server->width, &x))
        return 1;
    if (parse_coord(args[2], (long)server->height, &y))
        return 1;
    *x_out = (int)x;
    *y_out = (int)y;
    return 0;
}

/**
 * @brief Serialize the content of a single map tile and send it to the
 *        graphical client.
 *
 * The definitive protocol line is:
 * @code
 *   bct x y food linemate deraumere sibur mendiane phiras thystame\n
 * @endcode
 *
 * @param fd   Connected socket to the GUI client.
 * @param x    X coordinate of the tile (echoed in the reply).
 * @param y    Y coordinate of the tile (echoed in the reply).
 * @param t    Pointer to the tile’s @c resources_t structure
 *             (may be @c NULL during early start-up).
*/
static void send_bct_line(int fd, int x, int y, const resources_t *t)
{
    dprintf(fd, "bct %d %d %u %u %u %u %u %u %u\n", x, y,
        t->food, t->linemate, t->deraumere, t->sibur,
        t->mendiane, t->phiras, t->thystame);
}

void cmd_bct(server_t *server, int index, char **args)
{
    int x;
    int y;
    int fd;

    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    fd = server->poll.pollfds[index].fd;
    if (parse_bct_coords(args, server, &x, &y) != 0) {
        dprintf(fd, "ko\n");
        return;
    }
    send_bct_line(fd, x, y, &server->map[y][x]);
}
