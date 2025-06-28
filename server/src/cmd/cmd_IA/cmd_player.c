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
    char *buffer = NULL;

    if (asprintf(&buffer, "%u\n", server->poll.client_index) == -1)
        logger(server, "ASPRINTF : PLAYER INFO", PERROR, true);
    send_str(server, fd, buffer, true);
    if (asprintf(&buffer, "%u %u\n", server->width, server->height) == -1)
        logger(server, "ASPRINTF : SERV INFO", PERROR, true);
    send_str(server, fd, buffer, true);
}

void cmd_player(server_t *server, int index, teams_t *team)
{
    client_t *cl;
    int fd;

    cl = &server->poll.client_list[index];
    fd = server->poll.pollfds[index].fd;
    if (cl->whoAmI != UNKNOWN ||
        team->slots_used >= server->starter_eggs_number) {
        send_str(server, fd, "ko\n", false);
        return;
    }
    if (team->slots_used >= team->slots_max || team->egg == NULL) {
        send_str(server, fd, "ko\n", false);
        return;
    }
    add_player(server, index, team);
    cl->whoAmI = PLAYER;
    team->slots_used++;
    send_all_information(server, fd);
    event_ebo(server, index);
}
