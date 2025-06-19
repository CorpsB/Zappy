/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_new_gui_enw.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void send_enw(int fd, eggs_t *egg)
{
    dprintf(fd, "enw #%u #%u %u %u\n", egg->id, egg->creator_id,
        egg->position[0], egg->position[1]
    );
}

static void send_all_eggs(int fd, server_t *server)
{
    teams_t *team;
    eggs_t *egg;

    team = server->teams;
    egg = NULL;
    while (team) {
        egg = team->egg;
        while (egg) {
            send_enw(fd, egg);
            egg = egg->next;
        }
        team = team->next;
    }
}

void event_enw(server_t *server, player_t *player, eggs_t *egg)
{
    client_t *cl;
    int fd = 0;
    unsigned int id;

    if (!server || !egg)
        return;
    id = player ? player->id : (unsigned int)egg->creator_id;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI != GUI)
            continue;
        fd = server->poll.pollfds[i].fd;
        dprintf(fd,
            "enw #%u #%u %u %u\n", egg->id, id,
            egg->position[0], egg->position[1]
        );
    }
}

void event_new_gui_enw(server_t *server)
{
    client_t *cl = NULL;
    int fd = 0;

    if (!server)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI != GUI)
            continue;
        fd = server->poll.pollfds[i].fd;
        send_all_eggs(fd, server);
    }
}
