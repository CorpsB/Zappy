/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_sgt.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_sgt(server_t *server)
{
    int fd;
    client_t *cl;

    if (!server)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI == GUI) {
            fd = server->poll.pollfds[i].fd;
            dprintf(fd, "sgt %u\n", server->frequency);
        }
    }
}
