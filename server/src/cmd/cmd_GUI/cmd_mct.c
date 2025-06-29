/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_mct.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void event_bct_per_fd(server_t *server, int y, int x, int fd)
{
    char *buffer = NULL;
    resources_t tile = server->map[y][x];

    if (asprintf(&buffer, "bct %u %u %u %u %u %u %u %u %u\n",
        x, y, tile.food, tile.linemate,
        tile.deraumere, tile.sibur, tile.mendiane, tile.phiras,
        tile.thystame) == -1)
        logger(server, "BCT PER TILE", ERROR, true);
    send_str(server, fd, buffer, true);
}

void cmd_mct(server_t *server, int index, char **args)
{
    int fd;

    (void)args;
    if (!server || !server->poll.client_list || index < 0 ||
        index >= server->poll.client_index)
        return;
    fd = server->poll.pollfds[index].fd;
    for (unsigned y = 0; y < server->height; y++) {
        for (unsigned x = 0; x < server->width; x++) {
            event_bct_per_fd(server, y, x, fd);
        }
    }
}
