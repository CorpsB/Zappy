/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_player
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

//WARNING : This command is special. Don't put them on the cmd table.
/**
 * @brief Try to create and assign a player to a client.
 *
 * @return 0 on success, 1 on failure.
*/
static int create_and_assign_player(server_t *srv, int idx, teams_t *team)
{
    player_t *before;
    int fd;

    before = team->player;
    fd = srv->poll.pollfds[idx].fd;
    add_player(srv, fd, team);
    srv->poll.client_list[idx].player = team->player;
    if (team->player == before)
        return 1;
    return 0;
}

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
    if (create_and_assign_player(server, index, team)) {
        dprintf(fd, "ko\n");
        return;
    }
    cl->whoAmI = PLAYER;
    team->slots_used++;
    dprintf(fd, "ok\n");
    event_ebo(server, index);
}
