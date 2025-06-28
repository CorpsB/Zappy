/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** send_to_all_gui
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void send_to_all_gui(server_t *server, char *message)
{
    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI == GUI)
            dprintf(server->poll.pollfds[i].fd, "%s\n", message);
    }
    if (message)
        free(message);
    message = NULL;
}
