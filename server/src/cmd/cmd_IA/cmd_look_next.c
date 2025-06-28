/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** cmd_look_next
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static char *append_n_times(char *dst, const char *tok,
    unsigned int n, server_t *srv)
{
    for (unsigned int i = 0; i < n; ++i)
        dst = append_token(dst, tok, srv);
    return dst;
}

static char *tile_to_str(server_t *srv, int y, int x)
{
    char *str = NULL;
    size_t len;

    str = append_n_times(str, "player ", players_at(srv, y, x), srv);
    str = append_n_times(str, "egg ", eggs_at(srv, y, x), srv);
    str = append_n_times(str, "food ", srv->map[y][x].food, srv);
    str = append_n_times(str, "linemate ", srv->map[y][x].linemate, srv);
    str = append_n_times(str, "deraumere ", srv->map[y][x].deraumere, srv);
    str = append_n_times(str, "sibur ", srv->map[y][x].sibur, srv);
    str = append_n_times(str, "mendiane ", srv->map[y][x].mendiane, srv);
    str = append_n_times(str, "phiras ", srv->map[y][x].phiras, srv);
    str = append_n_times(str, "thystame ", srv->map[y][x].thystame, srv);
    if (!str)
        str = strdup("");
    else {
        len = strlen(str);
        if (len && str[len - 1] == ' ')
            str[len - 1] = '\0';
    }
    return str;
}

static void wrap_coordinates(server_t *server, int *x, int *y)
{
    if (*x < 0)
        *x += (int)server->width;
    if (*y < 0)
        *y += (int)server->height;
    if (*x >= (int)server->width)
        *x %= (int)server->width;
    if (*y >= (int)server->height)
        *y %= (int)server->height;
}

static char *line_top(server_t *srv, int y, int x, int lvl)
{
    char *ln = NULL;
    int cx;
    int cy;

    y -= lvl;
    x -= lvl;
    for (int i = 0; i < (lvl * 2 + 1); ++i) {
        cx = x + i;
        cy = y;
        wrap_coordinates(srv, &cx, &cy);
        ln = append_token(ln, tile_to_str(srv, cy, cx), srv);
        if (i < (lvl * 2))
            ln = append_token(ln, ", ", srv);
    }
    return ln;
}

static char *line_bottom(server_t *srv, int y, int x, int lvl)
{
    char *ln = NULL;
    int cx;
    int cy;

    y += lvl;
    x += lvl;
    for (int i = 0; i < (lvl * 2 + 1); ++i) {
        cx = x - i;
        cy = y;
        wrap_coordinates(srv, &cx, &cy);
        ln = append_token(ln, tile_to_str(srv, cy, cx), srv);
        if (i < (lvl * 2))
            ln = append_token(ln, ", ", srv);
    }
    return ln;
}

static char *line_left(server_t *srv, int y, int x, int lvl)
{
    char *ln = NULL;
    int cx;
    int cy;

    x -= lvl;
    y += lvl;
    for (int i = 0; i < (lvl * 2 + 1); ++i) {
        cx = x;
        cy = y - i;
        wrap_coordinates(srv, &cx, &cy);
        ln = append_token(ln, tile_to_str(srv, cy, cx), srv);
        if (i < (lvl * 2))
            ln = append_token(ln, ", ", srv);
    }
    return ln;
}

static char *line_right(server_t *srv, int y, int x, int lvl)
{
    char *ln = NULL;
    int cx;
    int cy;

    x += lvl;
    y -= lvl;
    for (int i = 0; i < (lvl * 2 + 1); ++i) {
        cx = x;
        cy = y + i;
        wrap_coordinates(srv, &cx, &cy);
        ln = append_token(ln, tile_to_str(srv, cy, cx), srv);
        if (i < (lvl * 2))
            ln = append_token(ln, ", ", srv);
    }
    return ln;
}

char *build_line(server_t *srv, player_t *pl, int lvl)
{
    static line_builder_t builders[4] = {
        line_top, line_right, line_bottom, line_left
    };

    return builders[pl->direction - 1](srv,
        (int)pl->position[0], (int)pl->position[1], lvl);
}
