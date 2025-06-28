/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** cm_broadcast_text2.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Allocates and initializes a broadcast distance map.
 * @param srv Pointer to the server structure.
 * @return A 2D int array representing the broadcast map, or NULL on failure.
*/
int **create_broadcast_map(server_t *srv)
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

/**
 * @brief Frees the memory of a broadcast map.
 * @param srv Pointer to the server structure.
 * @param map The 2D int array to free.
*/
void free_broadcast_map(server_t *srv, int **map)
{
    (void)srv;
    for (unsigned y = 0; map && y < srv->height; ++y)
        free(map[y]);
    free(map);
}

void send_same_tile_message(server_t *srv, player_t *rcv,
    const char *msg)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "message 0, %s\n", msg) == -1)
        logger(srv, "ASPRINTF : BROADCAST", PERROR, true);
    send_str(srv, rcv->socket_fd, buffer, true);
}

void send_directional_message(server_t *srv, player_t *snd,
    player_t *rcv, const char *msg)
{
    int raw;
    int adj;
    int **map;
    char *buffer = NULL;

    map = create_broadcast_map(srv);
    if (!map)
        return;
    propagate_sound_map(map, srv, snd);
    raw = get_raw_direction(map, srv, rcv);
    adj = adjust_to_player_dir(raw, rcv);
    if (asprintf(&buffer, "message %d, %s\n", adj, msg) == -1)
        logger(srv, "ASPRINTF : BROADCAST", PERROR, true);
    send_str(srv, rcv->socket_fd, buffer, true);
    free_broadcast_map(srv, map);
}
