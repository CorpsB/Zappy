/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_poll
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void see_a_pollfd(struct pollfd *pollfd, int index)
{
    if (!pollfd) {
        dprintf(2, "PollFD #%d: NULL\n", index);
        return;
    }

    dprintf(2, "PollFD #%d:\n", index);
    dprintf(2, "  fd      : %d\n", pollfd->fd);
    dprintf(2, "  events  : %d\n", pollfd->events);
    dprintf(2, "  revents : %d\n", pollfd->revents);
}


void see_pollfds(struct pollfd *pollfds, int size)
{
    dprintf(2, "===== POLLFD TABLE =====\n");
    for (int i = 0; i < size; i++) {
        see_a_pollfd(&pollfds[i], i);
    }
    dprintf(2, "========================\n");
}

void see_a_client(client_t *client)
{
    if (!client) {
        dprintf(2, "  [NULL client]\n");
        return;
    }
    dprintf(2, "  Type        : %s\n",
        client->whoAmI == PLAYER ? "PLAYER" :
        client->whoAmI == GUI    ? "GUI" :
        client->whoAmI == LISTEN ? "LISTEN" : "UNKNOWN");
    if (client->player) {
        dprintf(2, "  Player ID   : %u\n", client->player->id);
    } else {
        dprintf(2, "  No player associated.\n");
    }
}

void see_client_list(client_t *list)
{
    int i = 0;

    dprintf(2, "===== CLIENT LIST =====\n");
    while (list[i].whoAmI != END_OF_TABLE) {
        dprintf(2, "Client #%d:\n", i);
        see_a_client(&list[i]);
        i++;
    }
    dprintf(2, "========================\n");
}


void see_poll(poll_t poll)
{
    dprintf(2, "===== POLL STRUCTURE =====\n");
    dprintf(2, "Socket serveur      : %d\n", poll.socket);
    dprintf(2, "Client index actuel : %d\n", poll.client_index);

    if (poll.client_list == NULL) {
        dprintf(2, "Client list         : (null)\n");
    } else {
        dprintf(2, "Client list         : %p\n", (void *)poll.client_list);
    }

    if (poll.pollfds == NULL) {
        dprintf(2, "pollfds             : (null)\n");
    } else {
        dprintf(2, "pollfds             : %p\n", (void *)poll.pollfds);
    }

    dprintf(2, "Sockaddr.sin_family : %d\n", poll.sockaddr.sin_family);
    dprintf(2, "Sockaddr.sin_port   : %d\n", ntohs(poll.sockaddr.sin_port));
    dprintf(2, "Sockaddr.sin_addr   : %s\n", inet_ntoa(poll.sockaddr.sin_addr));
    dprintf(2, "==========================\n");
}
