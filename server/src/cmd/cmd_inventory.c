/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_inventory.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

int check_autorized(server_t *server, int index)
{
    client_t *cl;
    int fd;

    cl = &server->poll.client_list[index];
    fd = server->poll.pollfds[index].fd;
    if (cl->whoAmI != PLAYER || !cl->player) {
        dprintf(fd, "ko\n");
        return 1;
    }
    return 0;
}

void cmd_inventory(server_t *server, int index, const char **args)
{
    player_t *player;
    char buf[160];

    (void)args;
    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    if (check_autorized(server, index) != 0)
        return;
    player = server->poll.client_list[index].player;
    snprintf(buf, sizeof(buf),
        "[food %u , linemate %u , deraumere %u , sibur %u , "
        "mendiane %u , phiras %u , thystame %u , time %u]\n",
        player->inventory.food, player->inventory.linemate,
        player->inventory.deraumere, player->inventory.sibur,
        player->inventory.mendiane, player->inventory.phiras,
        player->inventory.thystame, player->cycle_before_death);
    dprintf(player->socket_fd, "%s", buf);
}
