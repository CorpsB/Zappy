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
    char *buffer = NULL;

    if (!server || !message)
        return;
    for (int i = 0; i < server->poll.connected_client; i++) {
        if (server->poll.client_list[i].whoAmI != GUI)
            continue;
        if (asprintf(&buffer, "%s\n", message) == -1)
            logger(server, "ASPRINTF : SEND TO ALL GUI", PERROR, true);
        send_str(server, server->poll.pollfds[i].fd, buffer, true);
    }
    free(message);
}
