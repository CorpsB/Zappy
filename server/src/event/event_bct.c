/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_bct.c
*/

/**
 * @file event_bct.c
 * @brief Implements events to send map tile resource updates to
 * graphical clients.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Provides functions to send the current resource content of the entire
 * map or individual tiles
 * to all connected graphical clients, following the "bct" protocol format.
 * These updates keep the GUI synchronized with the server's map state.
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
static void send_bct_tile(int fd, int y, int x, server_t *server)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "bct %u %u %u %u %u %u %u %u %u\n",
        x, y, server->map[y][x].food, server->map[y][x].linemate,
        server->map[y][x].deraumere, server->map[y][x].sibur,
        server->map[y][x].mendiane, server->map[y][x].phiras,
        server->map[y][x].thystame) == -1)
        logger(server, "BCT PER TILE", ERROR, true);
    send_str(server, fd, buffer, true);
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
            send_bct_tile(fd, y, x, server);
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
        x, y, tile.food, tile.linemate,
        tile.deraumere, tile.sibur, tile.mendiane, tile.phiras,
        tile.thystame) == -1)
        logger(server, "BCT PER TILE", ERROR, true);
    send_to_all_gui(server, buffer);
}
