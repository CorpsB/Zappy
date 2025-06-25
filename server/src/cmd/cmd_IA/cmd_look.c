/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_look.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static unsigned int get_player_on_team(server_t *, teams_t *tmp, int y, int x)
{
    unsigned int count = 0;

    for (player_t *player = tmp->player; player != NULL; player = player->next) {
        if ((int)player->position[0] == y && (int)player->position[1] == x)
            count++;
    }
    return count;
}

static unsigned int get_player_nbr(server_t *server, int y, int x)
{
    unsigned int count = 0;

    for (teams_t *tmp = server->teams; tmp != NULL; tmp = tmp->next) {
        count += get_player_on_team(server, tmp, y, x);
    }
    return count;
}

static unsigned int get_egg_on_team(server_t *, teams_t *tmp, int y, int x)
{
    unsigned int count = 0;

    for (eggs_t *egg = tmp->egg; egg != NULL; egg = egg->next) {
        if ((int)egg->position[0] == y && (int)egg->position[1] == x)
            count++;
    }
    return count;
}

static unsigned int get_egg_nbr(server_t *server, int y, int x)
{
    unsigned int count = 0;

    for (teams_t *tmp = server->teams; tmp != NULL; tmp = tmp->next) {
        count += get_egg_on_team(server, tmp, y, x);
    }
    return count;
}

static char *append_token(char *dest, const char *token, server_t *server) {
    char *new_str = NULL;

    if (dest == NULL) {
        if (asprintf(&new_str, "%s", token) == -1)
            logger(server, "ASPRINTF : LOOK", PERROR, true);
    } else {
        if (asprintf(&new_str, "%s %s", dest, token) == -1)
            logger(server, "ASPRINTF : LOOK", PERROR, true);
        if (dest)
            free(dest);
    }
    return new_str;
}

static char *look_per_tile(server_t *server, int y, int x)
{
    char *tile = NULL;

    for (unsigned int i = 0; i < get_egg_nbr(server, y, x); i++)
        tile = append_token(tile, "egg", server);
    for (unsigned int i = 0; i < get_player_nbr(server, x, y); i++)
        tile = append_token(tile, "player", server);
    for (unsigned int i = 0; i < server->map[y][x].food; i++)
        tile = append_token(tile, "food", server);
    for (unsigned int i = 0; i < server->map[y][x].linemate; i++)
        tile = append_token(tile, "linemate", server);
    for (unsigned int i = 0; i < server->map[y][x].deraumere; i++)
        tile = append_token(tile, "deraumere", server);
    for (unsigned int i = 0; i < server->map[y][x].sibur; i++)
        tile = append_token(tile, "sibur", server);
    for (unsigned int i = 0; i < server->map[y][x].mendiane; i++)
        tile = append_token(tile, "mendiane", server);
    for (unsigned int i = 0; i < server->map[y][x].phiras; i++)
        tile = append_token(tile, "phiras", server);
    for (unsigned int i = 0; i < server->map[y][x].thystame; i++)
        tile = append_token(tile, "thystame", server);
    return tile;
}

static void safe_pos_update(server_t *server, int *x, int *y)
{
    if (*y > (int)server->height)
        *y = *y % (int)server->height;
    if (*x > (int)server->width)
        *x = *x % (int)server->width;
    while (*y < 0)
        *y += (int)server->height;
    while (*x < 0)
        *x += (int)server->width;
}

static char *look_line_top(server_t *server, int y, int x, int lvl)
{
    char *line = NULL;
    char *tile_tmp;
    int line_size = lvl * 2 + 1;

    y -= lvl;
    x -= lvl;
    for (int i = 0; i < line_size; ++i) {
        int cur_x = x + i;
        int cur_y = y;
        safe_pos_update(server, &cur_x, &cur_y);
        tile_tmp = look_per_tile(server, cur_y, cur_x);
        line = append_token(line, tile_tmp, server);
        if (i < line_size - 1)
            line = append_token(line, " ", server);
        free(tile_tmp);
    }
    return line;
}

static char *look_line_bottom(server_t *server, int y, int x, int lvl)
{
    char *line = NULL;
    char *tile_tmp;
    int line_size = lvl * 2 + 1;

    y += lvl;
    x += lvl;
    for (int i = 0; i < line_size; ++i) {
        int cur_x = x - i;
        int cur_y = y;
        safe_pos_update(server, &cur_x, &cur_y);
        tile_tmp = look_per_tile(server, cur_y, cur_x);
        line = append_token(line, tile_tmp, server);
        if (i < line_size - 1)
            line = append_token(line, " ", server);
        free(tile_tmp);
    }
    return line;
}

static char *look_line_left(server_t *server, int y, int x, int lvl)
{
    char *line = NULL;
    char *tile_tmp;
    int line_size = lvl * 2 + 1;

    x -= lvl;
    y += lvl;
    for (int i = 0; i < line_size; ++i) {
        int cur_x = x;
        int cur_y = y - i;
        safe_pos_update(server, &cur_x, &cur_y);
        tile_tmp = look_per_tile(server, cur_y, cur_x);
        line = append_token(line, tile_tmp, server);
        if (i < line_size - 1)
            line = append_token(line, " ", server);
        free(tile_tmp);
    }
    return line;
}

static char *look_line_right(server_t *server, int y, int x, int lvl)
{
    char *line = NULL;
    char *tile_tmp;
    int line_size = lvl * 2 + 1;

    x += lvl;
    y -= lvl;
    for (int i = 0; i < line_size; ++i) {
        int cur_x = x;
        int cur_y = y + i;
        safe_pos_update(server, &cur_x, &cur_y);
        tile_tmp = look_per_tile(server, cur_y, cur_x);
        line = append_token(line, tile_tmp, server);
        if (i < line_size - 1)
            line = append_token(line, " ", server);
        free(tile_tmp);
    }
    return line;
}

static char *look_line(server_t *server, int y, int x, int lvl, player_t *player)
{
    if (player->direction == NORTH)
        return look_line_top(server, y, x, lvl);
    if (player->direction == SOUTH)
        return look_line_bottom(server, y, x, lvl);
    if (player->direction == EAST)
        return look_line_right(server, y, x, lvl);
    if (player->direction == WEST)
        return look_line_left(server, y, x, lvl);
    return NULL;
}

static char *look(server_t *server, player_t *player)
{
    char *result = strdup("[");
    char *line_tmp;

    for (unsigned int lvl = 0; lvl < player->lvl; lvl++) {
        line_tmp = look_line(server, player->position[1], player->position[0], lvl, player);
        result = append_token(result, line_tmp, server);
        if (lvl < player->lvl - 1)
            result = append_token(result, ", ", server);
        free(line_tmp);
    }
    result = append_token(result, "]", server);
    return result;
}

void cmd_look(server_t *server, int index, char **)
{
    player_t *player = server->poll.client_list[index].player;
    char *message;

    message = look(server, player);
    dprintf(player->socket_fd, "%s\n", message);
    if (message)
        free(message);
}