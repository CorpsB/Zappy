/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pdi.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Notify the GUI and the player that a player has died.
 *
 * GUI clients receive: pdi <id>
 * The player receives: dead
 *
 * @param server Pointer to the game server.
 * @param player Pointer to the player who has died.
 */
void event_pdi(server_t *server, player_t *player)
{
    client_t *cl;
    int fd;

    if (!server || !player)
        return;
    dprintf(player->socket_fd, "dead\n");
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        fd = server->poll.pollfds[i].fd;
        if (cl->whoAmI == GUI)
            dprintf(fd, "pdi %d\n", player->id);
    }
}

void event_pdi_by_index(void)
{
    return;
}
