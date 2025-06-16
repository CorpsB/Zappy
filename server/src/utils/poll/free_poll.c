/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** free_poll
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void free_poll(server_t *server)
{
    for (int i = 0; i < server->poll.connected_client; i++)
        close(server->poll.pollfds[i].fd);
    if (server->poll.client_list)
        free(server->poll.client_list);
    if (server->poll.pollfds)
        free(server->poll.pollfds);
}