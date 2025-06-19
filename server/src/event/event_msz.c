/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_msz
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Notify all GUI clients with the map size.
 *
 * @param server The main server structure containing map and clients.
 */
void event_msz(server_t *server)
{
    int fd;
    client_t *cl;

    if (!server)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI == GUI) {
            fd = server->poll.pollfds[i].fd;
            dprintf(fd, "msz %u %u\n", server->width, server->height);
        }
    }
}
