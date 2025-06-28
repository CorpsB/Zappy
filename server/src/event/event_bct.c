/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_bct.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Send the resource content of a specific map tile to a graphical
 * client.
 * Format sent follows the protocol:
 * @code
 * bct X Y food linemate deraumere sibur mendiane phiras thystame\n
 * @endcode
 * @param fd File descriptor of the graphical client.
 * @param x X coordinate of the tile.
 * @param y Y coordinate of the tile.
 * @param tile Pointer to the resources structure of the tile.
*/
static void send_bct_tile(int fd, int x, int y, resources_t *tile)
{
    dprintf(fd,
        "bct %d %d %u %u %u %u %u %u %u\n", x, y, tile->food, tile->linemate,
        tile->deraumere, tile->sibur, tile->mendiane, tile->phiras,
        tile->thystame
    );
}

/**
 * @brief Send the entire map content to a graphical client.
 * Iterates over all tiles of the map and sends their resource content
 * using the "bct" protocol line.
 * @param fd File descriptor of the graphical client.
 * @param server Pointer to the global server structure.
*/
static void send_full_map(int fd, server_t *server)
{
    for (int y = 0; y < (int)server->height; y++) {
        for (int x = 0; x < (int)server->width; x++)
            send_bct_tile(fd, x, y, &server->map[y][x]);
    }
}

void event_bct(server_t *server)
{
    client_t *cl;
    int fd = 0;

    cl = NULL;
    if (!server || !server->map)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI != GUI)
            continue;
        fd = server->poll.pollfds[i].fd;
        send_full_map(fd, server);
    }
}

void event_bct_per_tile(server_t *server, int y, int x)
{
    char *buffer = NULL;
    resources_t tile = server->map[y][x];

    if (asprintf(&buffer, "bct %u %u %u %u %u %u %u %u %u",
        y, x, tile.food, tile.linemate,
        tile.deraumere, tile.sibur, tile.mendiane, tile.phiras,
        tile.thystame) == -1)
        logger(server, "BCT PER TILE", ERROR, true);
    send_to_all_gui(server, buffer);
}
