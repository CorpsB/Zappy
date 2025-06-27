/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_inventory
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_inventory(server_t *server, int index, const char **args)
{
    player_t *player;
    char buf[160];

    (void)args;
    if (!server || !server->poll.client_list ||
        index < 0 || index >= server->poll.client_index)
        return;
    player = server->poll.client_list[index].player;
    snprintf(buf, sizeof(buf),
        "[food %u, linemate %u, deraumere %u, sibur %u, "
        "mendiane %u, phiras %u, thystame %u]\n",
        player->inventory.food, player->inventory.linemate,
        player->inventory.deraumere, player->inventory.sibur,
        player->inventory.mendiane, player->inventory.phiras,
        player->inventory.thystame);
    dprintf(player->socket_fd, "%s", buf);
}
