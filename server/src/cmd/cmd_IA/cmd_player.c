/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_player
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void send_all_information(server_t *server, int fd)
{
    dprintf(fd, "ok\n");
    dprintf(fd, "%u\n", server->poll.client_index);
    dprintf(fd, "%u %u\n", server->width, server->height);
}

void cmd_player(server_t *server, int index, teams_t *team)
{
    printf("coucou\n");
    client_t *cl;
    int fd;

    cl = &server->poll.client_list[index];
    fd = server->poll.pollfds[index].fd;
    if (cl->whoAmI != UNKNOWN ||
        team->slots_used >= server->starter_eggs_number) {
        dprintf(fd, "ko\n");
        return;
    }
    if (team->slots_used >= team->slots_max || team->egg == NULL) {
        dprintf(fd, "ko\n");
        return;
    }
    add_player(server, index, team);
    cl->whoAmI = PLAYER;
    team->slots_used++;
    send_all_information(server, fd);
    event_ebo(server, index);
}
