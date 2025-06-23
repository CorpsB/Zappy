/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_tna.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void send_team_name(int fd, const char *name)
{
    if (!name)
        return;
    dprintf(fd, "tna %s\n", name);
}

static void send_all_teams(int fd, server_t *server)
{
    teams_t *team;

    team = server->teams;
    while (team) {
        send_team_name(fd, team->name);
        team = team->next;
    }
}

void event_tna(server_t *server)
{
    client_t *cl;
    int fd = 0;

    cl = NULL;
    if (!server || !server->teams)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI != GUI)
            continue;
        fd = server->poll.pollfds[i].fd;
        send_all_teams(fd, server);
    }
}
