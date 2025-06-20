/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_player
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_player(server_t *server, int index, teams_t *team)
{
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
    dprintf(fd, "ok\n");
    event_ebo(server, index);
}
