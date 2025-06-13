/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** graphic
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_graphic(server_t *server, int index, char **/*args*/)
{
    if (server->poll.client_list[index].whoAmI == UNKNOWN) {
        server->poll.client_list[index].whoAmI = GUI;
        dprintf(server->poll.pollfds[index].fd, "ok\n");
    } else {
        dprintf(server->poll.pollfds[index].fd, "ko\n");
    }
}