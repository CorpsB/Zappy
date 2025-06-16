/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_server
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void see_server(struct server *server, int fd)
{
    dprintf(fd, "====== SERVER STATE ======\n");
    dprintf(fd, "\tco           : \t\t%u\n",
        server->max_connections_per_team);
    dprintf(fd, "\tfrequency    : \t\t%u\n", server->frequency);
    dprintf(fd, "\tport         : \t\t%u\n", server->port);
    dprintf(fd, "\twidth        : \t\t%u\n", server->width);
    dprintf(fd, "\theight       : \t\t%u\n", server->height);
    dprintf(fd, "\teggs_count   : \t\t%u\n", server->eggs_count);
    dprintf(fd, "\tplayer_count : \t\t%u\n", server->player_count);
    dprintf(fd, "\tteams_count  : \t\t%u\n", server->teams_count);
    dprintf(fd, "\tdebug        : \t\t%s\n", server->debug ? "true" : "false");
    dprintf(fd, "\tdebug_fd     : \t\t%d\n\n", server->debug_fd);
    dprintf(fd, "====== END SERVER ======\n\n");
    see_poll(server->poll, fd, server->poll.connected_client);
    see_teams(server->teams, fd);
}

void debug_server(server_t *server)
{
    if (!server) {
        logger(server, "SERVER DOESN'T EXIST", ERROR, true);
        return;
    }
    if (server->debug && server->debug_fd > 0)
        see_server(server, server->debug_fd);
    see_server(server, 2);
}
