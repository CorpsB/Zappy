/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_bct.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void send_bct_tile(int fd, int x, int y, resources_t *tile)
{
    dprintf(fd,
        "bct %d %d %u %u %u %u %u %u %u\n", x, y, tile->food, tile->linemate,
        tile->deraumere, tile->sibur, tile->mendiane, tile->phiras,
        tile->thystame
    );
}

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
