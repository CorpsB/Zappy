/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_ebo.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void send_ebo(int fd, unsigned int egg_id)
{
    dprintf(fd, "ebo #%u\n", egg_id);
}

void event_ebo(server_t *server, unsigned int egg_id)
{
    client_t *cl;
    int fd;

    fd = 0;
    if (!server)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI != GUI)
            continue;
        fd = server->poll.pollfds[i].fd;
        send_ebo(fd, egg_id);
    }
}
