/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_edi.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_edi(server_t *server, unsigned int egg_id)
{
    client_t *cl;
    int fd;

    cl = NULL;
    fd = 0;
    if (!server)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI != GUI)
            continue;
        fd = server->poll.pollfds[i].fd;
        dprintf(fd, "edi #%u\n", egg_id);
    }
}
