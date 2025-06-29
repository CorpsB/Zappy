/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_new_gui_enw.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void send_enw(server_t *server, int fd, eggs_t *egg)
{
    char *buffer = NULL;

    if (!egg || !server)
        return;
    if (asprintf(&buffer, "enw #%u #%d %u %u\n",
        egg->id, egg->creator_id, egg->position[0], egg->position[1]) == -1)
        logger(server, "ASPRINTF : ENW", PERROR, true);
    send_str(server, fd, buffer, true);
}

/**
 * @brief Send an "enw" message for every egg in the game to a graphical
 * client.
 * Typically called when a new graphical client connects, so they
 * can get information about all existing eggs.
 * @param fd File descriptor of the graphical client.
 * @param server Pointer to the global server structure.
*/
static void send_all_eggs(server_t *server, int fd)
{
    teams_t *team;
    eggs_t *egg;

    if (!server)
        return;
    for (team = server->teams; team; team = team->next) {
        for (egg = team->egg; egg; egg = egg->next)
            send_enw(server, fd, egg);
    }
}

void event_enw(server_t *server, player_t *player)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "enw #%u #%d %u %u",
        server->eggs_count - 1, player->id, player->position[0], player->position[1]) == -1)
        logger(server, "ENW", ERROR, true);
    send_to_all_gui(server, buffer);
}

void event_new_gui_enw(server_t *server)
{
    client_t *cl;
    int fd;

    if (!server)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        cl = &server->poll.client_list[i];
        if (cl->whoAmI != GUI)
            continue;
        fd = server->poll.pollfds[i].fd;
        send_all_eggs(server, fd);
    }
}
