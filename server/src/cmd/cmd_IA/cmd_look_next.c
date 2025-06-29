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
    if (dst && dst[0] != '\0' && dst[strlen(dst) - 1] != ' ')
        dst = append_token(dst, " ", srv);
    for (unsigned int i = 0; i < n; ++i) {
        dst = append_token(dst, tok, srv);
        if (i < n - 1)
            dst = append_token(dst, " ", srv);
    }
    return dst;
}

static char *tile_to_str(server_t *srv, int y, int x)
{
    char *str = NULL;

    str = append_n_times(str, "player", players_at(srv, y, x), srv);
    str = append_n_times(str, "egg", eggs_at(srv, y, x), srv);
    str = append_n_times(str, "food", srv->map[y][x].food, srv);
    str = append_n_times(str, "linemate", srv->map[y][x].linemate, srv);
    str = append_n_times(str, "deraumere", srv->map[y][x].deraumere, srv);
    str = append_n_times(str, "sibur", srv->map[y][x].sibur, srv);
    str = append_n_times(str, "mendiane", srv->map[y][x].mendiane, srv);
    str = append_n_times(str, "phiras", srv->map[y][x].phiras, srv);
    str = append_n_times(str, "thystame", srv->map[y][x].thystame, srv);
    if (!str)
        str = strdup("");
    if (!str)
        logger(srv, "STRDUP : LOOK", PERROR, true);
    return str;
}

static void wrap_coordinates(server_t *server, int *x, int *y)
{
    while (*x < 0)
        *x += (int)server->width;
    while (*y < 0)
        *y += (int)server->height;
    if (*x >= (int)server->width)
        *x %= (int)server->width;
    if (*y >= (int)server->height)
        *y %= (int)server->height;
}

static char *look_line(server_t *srv, unsigned int *pos, int *offset, int lvl)
{
    char *line = NULL;
    char *tile_tmp;
    int line_size = lvl * 2;
    int coord[2] = {pos[0], pos[1]};

    coord[0] += (lvl * offset[0]);
    coord[1] += (lvl * offset[1]);
    for (int i = 0; i < line_size + 1; ++i) {
        wrap_coordinates(srv, &coord[0], &coord[1]);
        tile_tmp = tile_to_str(srv, coord[1], coord[0]);
        line = append_token(line, tile_tmp, srv);
        if (i < line_size)
            line = append_token(line, ", ", srv);
        free(tile_tmp);
        coord[0] += offset[2];
        coord[1] += offset[3];
    }
    return line;
}

char *build_line(server_t *srv, player_t *pl, int lvl)
{
    int offset_n[4] = {-1, -1, 1, 0};
    int offset_e[4] = {1, -1, 0, 1};
    int offset_s[4] = {1, 1, -1, 0};
    int offset_w[4] = {-1, 1, 0, -1};

    switch (pl->direction) {
        case NORTH:
            return look_line(srv, pl->position, offset_n, lvl);
        case EAST:
            return look_line(srv, pl->position, offset_e, lvl);
        case SOUTH:
            return look_line(srv, pl->position, offset_s, lvl);
        default:
            return look_line(srv, pl->position, offset_w, lvl);
    }
}
