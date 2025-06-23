/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_poll
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void see_a_pollfd(struct pollfd *pollfd, int index, int fd)
{
    if (!pollfd) {
        dprintf(fd, "PollFD #%d: NULL\n", index);
        return;
    }
    dprintf(fd, "PollFD #%d:\n", index);
    dprintf(fd, "  fd      : %d\n", pollfd->fd);
    dprintf(fd, "  events  : %d\n", pollfd->events);
    dprintf(fd, "  revents : %d\n", pollfd->revents);
}

void see_pollfds(struct pollfd *pollfds, int fd, int size)
{
    dprintf(fd, "====== POLLFD TABLE ======\n");
    for (int i = 0; i < size; i++) {
        see_a_pollfd(&pollfds[i], i, fd);
    }
    dprintf(fd, "==========================\n\n");
}

void see_a_client(client_t *client, int fd)
{
    if (!client) {
        dprintf(fd, "  [NULL client]\n");
        return;
    }
    if (client->whoAmI == PLAYER)
        dprintf(fd, "  Type        : PLAYER\n");
    if (client->whoAmI == GUI)
        dprintf(fd, "  Type        : GUI\n");
    if (client->whoAmI == LISTEN)
        dprintf(fd, "  Type        : LISTEN\n");
    if (client->whoAmI == UNKNOWN)
        dprintf(fd, "  Type        : UNKNOWN\n");
    if (client->player) {
        dprintf(fd, "  Player ID   : %u\n", client->player->id);
    } else {
        dprintf(fd, "  No player associated.\n");
    }
}

void see_client_list(client_t *list, int fd, int size)
{
    int i = 0;

    dprintf(fd, "====== CLIENT LIST ======\n");
    while (i < size) {
        dprintf(fd, "Client #%d:\n", i);
        see_a_client(&list[i], fd);
        i++;
    }
}

void see_poll(poll_t poll, int fd, int size)
{
    dprintf(fd, "====== POLL STRUCTURE ======\n");
    dprintf(fd, "Server socket      : %d\n", poll.socket);
    dprintf(fd, "Current client index : %d\n", poll.client_index);
    dprintf(fd, "Number of connected clients : %d\n", poll.connected_client);
    if (poll.client_list == NULL)
        dprintf(fd, "Client list         : (null)\n");
    else
        dprintf(fd, "Client list         : %p\n", (void *)poll.client_list);
    if (poll.pollfds == NULL)
        dprintf(fd, "pollfds             : (null)\n");
    else
        dprintf(fd, "pollfds             : %p\n", (void *)poll.pollfds);
    dprintf(fd, "Sockaddr.sin_family : %d\n", poll.sockaddr.sin_family);
    dprintf(fd, "Sockaddr.sin_port   : %d\n", ntohs(poll.sockaddr.sin_port));
    dprintf(fd, "Sockaddr.sin_addr   : %s\n\n",
        inet_ntoa(poll.sockaddr.sin_addr));
    dprintf(fd, "====== END POLL STRUCT ======\n\n");
    see_pollfds(poll.pollfds, fd, size);
    see_client_list(poll.client_list, fd, size);
    dprintf(fd, "==========================\n\n");
}
