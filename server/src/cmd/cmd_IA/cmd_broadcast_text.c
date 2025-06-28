/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_broadcast_text.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void safe_pos_update(server_t *srv, int *x, int *y)
{
    if (*y >= (int)srv->height)
        *y %= (int)srv->height;
    if (*x >= (int)srv->width)
        *x %= (int)srv->width;
    while (*y < 0)
        *y += (int)srv->height;
    while (*x < 0)
        *x += (int)srv->width;
}

static int **create_broadcast_map(server_t *srv)
{
    int **map = malloc(sizeof(int *) * srv->height);

    if (!map)
        return NULL;
    for (unsigned y = 0; y < srv->height; ++y) {
        map[y] = malloc(sizeof(int) * srv->width);
        if (!map[y]) {
            free_int_map(y, map);
            logger(srv, "INTMAP : BROADCAST", PERROR, true);
        }
        for (unsigned x = 0; x < srv->width; ++x)
            map[y][x] = -1;
    }
    return map;
}

static void free_broadcast_map(server_t *srv, int **map)
{
    (void)srv;
    for (unsigned y = 0; map && y < srv->height; ++y)
        free(map[y]);
    free(map);
}

static void propagate_sound_map_tile(int **map, server_t *srv,
    int *pos, int val)
{
    int up[2] = { pos[0], pos[1] - 1 };
    int down[2] = { pos[0], pos[1] + 1 };
    int left[2] = { pos[0] - 1, pos[1] };
    int right[2] = { pos[0] + 1, pos[1] };

    safe_pos_update(srv, &pos[0], &pos[1]);
    if (!(val < map[pos[1]][pos[0]] && map[pos[1]][pos[0]] != -1))
        return;
    map[pos[1]][pos[0]] = val;
    propagate_sound_map_tile(map, srv, up, val + 1);
    propagate_sound_map_tile(map, srv, left, val + 1);
    propagate_sound_map_tile(map, srv, right, val + 1);
    propagate_sound_map_tile(map, srv, down, val + 1);
}

static void propagate_sound_map(int **map, server_t *srv,
    player_t *sender)
{
    map[sender->position[1]][sender->position[0]] = 0;
    propagate_sound_map_tile(map, srv, (int *)sender->position, 0);
}

static int get_tile_dist(int **map, server_t *srv, int x, int y)
{
    safe_pos_update(srv, &x, &y);
    return map[y][x];
}

static int get_raw_direction(int **map, server_t *srv, player_t *rcv)
{
    int x = rcv->position[0];
    int y = rcv->position[1];
    int d[8] = {
        get_tile_dist(map, srv, x, y - 1),
        get_tile_dist(map, srv, x - 1, y - 1),
        get_tile_dist(map, srv, x - 1, y),
        get_tile_dist(map, srv, x - 1, y + 1),
        get_tile_dist(map, srv, x, y + 1),
        get_tile_dist(map, srv, x + 1, y + 1),
        get_tile_dist(map, srv, x + 1, y),
        get_tile_dist(map, srv, x + 1, y - 1)
    };
    int idx = 0;

    for (int i = 1; i < 8; ++i)
        if (d[i] < d[idx])
            idx = i;
    return idx + 1;
}

static int adjust_to_player_dir(int raw, player_t *pl)
{
    int idx_raw = raw - 1;
    int idx_rot = (idx_raw - pl->direction * 2 + 8) % 8;

    return idx_rot + 1;
}

static void send_broadcast_to_rcv(server_t *srv, player_t *snd,
    player_t *rcv, const char *msg)
{
    int raw;
    int adj;
    int **map;

    if (snd->position[0] == rcv->position[0] &&
        snd->position[1] == rcv->position[1]) {
        dprintf(rcv->socket_fd, "message 0, %s\n", msg);
        return;
    }
    map = create_broadcast_map(srv);
    if (!map)
        return;
    propagate_sound_map(map, srv, snd);
    raw = get_raw_direction(map, srv, rcv);
    adj = adjust_to_player_dir(raw, rcv);
    dprintf(rcv->socket_fd, "message %d, %s\n", adj, msg);
    free_broadcast_map(srv, map);
}

void cmd_broadcast_text(server_t *srv, int idx, char **args)
{
    player_t *snd = srv->poll.client_list[idx].player;
    char *msg = NULL;

    for (int i = 1; args[i]; ++i) {
        msg = append_token(msg, args[i], srv);
        if (args[i + 1])
            msg = append_token(msg, " ", srv);
    }
    for (int i = 0; i < srv->poll.connected_client; ++i)
        if (srv->poll.client_list[i].whoAmI == PLAYER &&
            srv->poll.client_list[i].player != snd &&
            !srv->poll.client_list[i].player->is_dead)
            send_broadcast_to_rcv(srv, snd,
                srv->poll.client_list[i].player, msg);
    event_pbc(srv, snd, msg);
    free(msg);
}
