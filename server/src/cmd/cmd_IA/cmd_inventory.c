/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_inventory
*/

/**
 * @file cmd_inventory.c
 * @brief Implements the "inventory" command to send player's inventory
 * contents.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Retrieves the quantities of all resource types in the player's inventory,
 * formats them into a string, and sends this information back to the
 * player's client.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_inventory(server_t *server, int index, const char **args)
{
    player_t *player;
    char buf[160];
    char *buffer = NULL;

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
    if (asprintf(&buffer, "%s", buf) == -1)
        logger(server, "ASPRINTF : INVENTORY", PERROR, true);
    send_str(server, player->socket_fd, buffer, true);
}
