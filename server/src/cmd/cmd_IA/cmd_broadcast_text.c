/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_broadcast_text.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Safely wraps the given position around the map edges.
 * @param srv Pointer to the server structure.
 * @param x Pointer to the X coordinate to update.
 * @param y Pointer to the Y coordinate to update.
*/
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

/**
 * @brief Recursively propagates sound distance values to adjacent tiles.
 * @param map The 2D broadcast map.
 * @param srv Pointer to the server structure.
 * @param pos Array of size 2 representing the position [x, y].
 * @param val The current distance value to propagate.
*/
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

void propagate_sound_map(int **map, server_t *srv,
    player_t *sender)
{
    int sender_pos[2] = {sender->position[0], sender->position[1]};

    map[sender_pos[1]][sender_pos[0]] = 0;
    propagate_sound_map_tile(map, srv, sender_pos, 0);
}

/**
 * @brief Retrieves the broadcast distance for a given tile,
 * accounting for map wrapping.
 * @param map The 2D broadcast map.
 * @param srv Pointer to the server structure.
 * @param x The X coordinate.
 * @param y The Y coordinate.
 * @return The distance value for the tile.
*/
static int get_tile_dist(int **map, server_t *srv, int x, int y)
{
    safe_pos_update(srv, &x, &y);
    return map[y][x];
}

int get_raw_direction(int **map, server_t *srv, player_t *rcv)
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

int adjust_to_player_dir(int raw, player_t *pl)
{
    int idx_raw = raw - 1;
    int idx_rot = (idx_raw - pl->direction * 2 + 8) % 8;

    return idx_rot + 1;
}

/**
 * @brief Sends a broadcast message to a specific player.
 * If the sender and receiver are on the same tile, sends
 * a simple broadcast with direction 0.
 * Otherwise, calculates the direction based on map topology
 * and player orientation, then sends the directional message.
 * @param srv Pointer to the server structure.
 * @param snd Pointer to the sending player.
 * @param rcv Pointer to the receiving player.
 * @param msg The message to send.
*/
void send_broadcast_to_rcv(server_t *srv, player_t *snd,
    player_t *rcv, const char *msg)
{
    if (snd->position[0] == rcv->position[0] &&
            snd->position[1] == rcv->position[1]) {
        send_same_tile_message(srv, rcv, msg);
        return;
    }
    send_directional_message(srv, snd, rcv, msg);
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
    msg[strlen(msg) - 1] = '\0';
    for (int i = 0; i < srv->poll.connected_client; ++i)
        if (srv->poll.client_list[i].whoAmI == PLAYER &&
            srv->poll.client_list[i].player != snd &&
            !srv->poll.client_list[i].player->is_dead)
            send_broadcast_to_rcv(srv, snd,
                srv->poll.client_list[i].player, msg);
    event_pbc(srv, snd, msg);
    send_str(srv, snd->socket_fd, "ok\n", false);
    free(msg);
}
