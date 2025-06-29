/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_broadcast_text.c
*/

/**
 * @file broadcast_text.c
 * @brief Implements player message broadcasting with directional sound
 * calculation.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * Handles the "broadcast" command allowing a player to send messages
 * to all
 * other players. Calculates the direction of the message relative to
 * each receiver
 * based on map wrapping and player positions, then sends the message
 * with direction.
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
    if (map[pos[1]][pos[0]] != -1 && (val >= map[pos[1]][pos[0]] ||
    map[pos[1]][pos[0]] < 1))
        return;
    map[pos[1]][pos[0]] = val;
    propagate_sound_map_tile(map, srv, up, val + 1);
    propagate_sound_map_tile(map, srv, left, val + 1);
    propagate_sound_map_tile(map, srv, right, val + 1);
    propagate_sound_map_tile(map, srv, down, val + 1);
}

void propagate_sound_map(int **map, server_t *srv, player_t *sender)
{
    int sender_pos[2] = { sender->position[0], sender->position[1] };

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
    int dir = pl->direction;

    if (dir == EAST)
        dir = WEST;
    else if (dir == WEST)
        dir = EAST;
    return ((raw - 1 - ((dir - 1) * 2) + 8) % 8) + 1;
}

static void send_dir_message(server_t *srv, player_t *rcv,
    const char *msg, int **map)
{
    int raw = get_raw_direction(map, srv, rcv);
    int adj = adjust_to_player_dir(raw, rcv);
    char *buffer = NULL;

    if (asprintf(&buffer, "message %d, %s\n", adj, msg) == -1)
        logger(srv, "ASPRINTF BROADCAST", PERROR, true);
    send_str(srv, rcv->socket_fd, buffer, true);
}

static char *concat_broadcast_msg(char **args, server_t *srv)
{
    char *msg = NULL;

    for (int i = 1; args[i]; ++i) {
        msg = append_token(msg, args[i], srv);
        if (args[i + 1])
            msg = append_token(msg, " ", srv);
    }
    msg[strlen(msg) - 1] = '\0';
    return msg;
}

static void send_broadcast_to_all(server_t *srv, player_t *snd,
    const char *msg, int **map)
{
    player_t *rcv = NULL;

    for (int i = 0; i < srv->poll.connected_client; ++i) {
        rcv = srv->poll.client_list[i].player;
        if (is_valid_rcv(srv, rcv, snd, i))
            send_dir_message(srv, rcv, msg, map);
    }
}

void cmd_broadcast_text(server_t *srv, int idx, char **args)
{
    player_t *snd = srv->poll.client_list[idx].player;
    char *msg = NULL;
    int **map = NULL;

    if (check_sender(snd))
        return;
    msg = concat_broadcast_msg(args, srv);
    map = create_broadcast_map(srv);
    if (!map) {
        free(msg);
        return;
    }
    propagate_sound_map(map, srv, snd);
    send_broadcast_to_all(srv, snd, msg, map);
    free_broadcast_map(srv, map);
    event_pbc(srv, snd, msg);
    send_str(srv, snd->socket_fd, "ok\n", false);
    free(msg);
}
