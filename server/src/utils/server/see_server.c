/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_server
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void log_see_server(server_t *server)
{
    int fd = server->debug_fd;

    if (fd <= 0) {
        logger(server, "DEBUG FD ERROR", INFO, false);
        return;
    }
    dprintf(fd, "===== SERVER STATE =====\n");
    dprintf(fd, "\tco           : \t\t%u\n", server->max_connections_per_team);
    dprintf(fd, "\tfrequency    : \t\t%u\n", server->frequency);
    dprintf(fd, "\tport         : \t\t%u\n", server->port);
    dprintf(fd, "\twidth        : \t\t%u\n", server->width);
    dprintf(fd, "\theight       : \t\t%u\n", server->height);
    dprintf(fd, "\teggs_count   : \t\t%u\n", server->eggs_count);
    dprintf(fd, "\tplayer_count : \t\t%u\n", server->player_count);
    dprintf(fd, "\tteams_count  : \t\t%u\n", server->teams_count);
    dprintf(fd, "\tdebug        : \t\t%s\n", server->debug ? "true" : "false");
    dprintf(fd, "\tdebug_fd     : \t\t%d\n", server->debug_fd);
}

void see_server(struct server *server)
{
    if (!server) {
        logger(server, "SERVER DOESN'T EXIST", ERROR, true);
        return;
    }
    if (server->debug)
        log_see_server(server);
    dprintf(2, "===== SERVER STATE =====\n");
    dprintf(2, "\tco           : \t\t%u\n", server->max_connections_per_team);
    dprintf(2, "\tfrequency    : \t\t%u\n", server->frequency);
    dprintf(2, "\tport         : \t\t%u\n", server->port);
    dprintf(2, "\twidth        : \t\t%u\n", server->width);
    dprintf(2, "\theight       : \t\t%u\n", server->height);
    dprintf(2, "\teggs_count   : \t\t%u\n", server->eggs_count);
    dprintf(2, "\tplayer_count : \t\t%u\n", server->player_count);
    dprintf(2, "\tteams_count  : \t\t%u\n", server->teams_count);
    dprintf(2, "\tdebug        : \t\t%s\n", server->debug ? "true" : "false");
    dprintf(2, "\tdebug_fd     : \t\t%d\n", server->debug_fd);
    see_poll(server->poll);
    see_teams(server->teams);
    // see_teams(server->teams);
    // dprintf(2, "===== END =====\n"); //=>A ajouter à la fin de teams
}
