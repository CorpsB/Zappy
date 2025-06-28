/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** poll
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void init_server(server_t *server)
{
    socklen_t size = sizeof(struct sockaddr_in);

    server->poll.socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->poll.socket == -1)
        logger(server, "SOCKET", PERROR, true);
    memset(&server->poll.sockaddr, 0, size);
    server->poll.sockaddr.sin_family = AF_INET;
    server->poll.sockaddr.sin_port = htons(server->port);
    server->poll.sockaddr.sin_addr.s_addr = INADDR_ANY;
    server->poll.connected_client = 0;
    server->poll.client_index = 0;
    if (bind(server->poll.socket, (struct sockaddr *)&server->poll.sockaddr,
        size) == -1)
        logger(server, "SOCKET BIND", PERROR, true);
    if (listen(server->poll.socket, 200) == -1)
        logger(server, "LISTEN", PERROR, true);
}

static void add_client(server_t *server, int socket, whoAmI_t state)
{
    server->poll.pollfds = realloc(
        server->poll.pollfds,
        sizeof(struct pollfd) * (server->poll.client_index + 1));
    server->poll.client_list = realloc(
        server->poll.client_list,
        sizeof(client_t) * (server->poll.client_index + 1));
    if (!server->poll.pollfds || !server->poll.client_list)
        logger(server, "REALLOC", PERROR, true);
    server->poll.pollfds[server->poll.client_index].fd = socket;
    server->poll.pollfds[server->poll.client_index].events = POLLIN;
    server->poll.pollfds[server->poll.client_index].revents = 0;
    server->poll.client_list[server->poll.client_index].whoAmI = state;
    server->poll.client_list[server->poll.client_index].player = NULL;
    if (state == UNKNOWN)
        dprintf(server->poll.pollfds[server->poll.client_index].fd,
            "WELCOME\n");
    server->poll.client_index++;
    server->poll.connected_client++;
    logger(server, "AJOUT D'UN CLIENT", DEBUG, false);
    see_poll(server->poll, 2, server->poll.connected_client);
}

static bool is_game_over(server_t *server)
{
    for (teams_t *teams = server->teams; teams != NULL; teams = teams->next) {
        if (teams->win) {
            event_seg(server, teams->name);
            return true;
        }
    }
    return false;
}

static bool del_client(server_t *server, int index)
{
    close(server->poll.pollfds[index].fd);
    for (int i = 0; i < server->poll.connected_client; i++) {
        if (i > index) {
            server->poll.client_list[i - 1] = server->poll.client_list[i];
            server->poll.pollfds[i - 1] = server->poll.pollfds[i];
        }
    }
    server->poll.connected_client--;
    server->poll.client_index--;
    server->poll.client_list = realloc(server->poll.client_list,
        sizeof(client_t) * server->poll.connected_client);
    server->poll.pollfds = realloc(server->poll.pollfds,
        sizeof(struct pollfd) * server->poll.connected_client);
    if (!server->poll.pollfds || !server->poll.client_list)
        logger(server, "REALLOC", PERROR, true);
    event_pdi_by_index(server, index);
    return true;
}

static void add_cmd(server_t *server, char *cmd, int index)
{
    player_t *pl;

    if (server->poll.client_list[index].whoAmI != PLAYER)
        return cmd_parser(server, index, cmd);
    pl = server->poll.client_list[index].player;
    for (int i = 0; i < 10; i++) {
        if (pl->cmd[i] == NULL) {
            pl->cmd[i] = cmd;
            break;
        }
    }
}

static bool event_detector(server_t *server, int i)
{
    int bytes;
    int client_fd;
    char cmd[1024];

    if (server->poll.pollfds[i].revents & POLLIN) {
        if (server->poll.client_list[i].whoAmI == LISTEN) {
            client_fd = accept(server->poll.pollfds[i].fd, NULL, NULL);
            add_client(server, client_fd, UNKNOWN);
            return true;
        }
        bytes = read(server->poll.pollfds[i].fd, cmd, sizeof(cmd));
        if (bytes <= 0)
            return del_client(server, i);
        cmd[bytes] = '\0';
        add_cmd(server, cmd, i);
        return true;
    }
    return false;
}

static void poll_func(server_t *server, zappy_clock_t *clock)
{
    int event;
    int t = (unsigned int)
    ((1.0 - clock->accumulator) * 1000.0 / clock->freq);

    event = poll(server->poll.pollfds, server->poll.client_index, (int)t);
    if (event == -1)
        logger(server, "POLL", PERROR, true);
    if (event == 0)
        return;
    for (int i = 0; i < server->poll.client_index; i++) {
        if (event_detector(server, i))
            return;
    }
}

static void eat_per_teams(server_t *server, teams_t *teams)
{
    for (player_t *tmp = teams->player; tmp != NULL; tmp = tmp->next) {
        if (tmp->is_dead)
            continue;
        if ((int)tmp->cycle_before_death - 1 <= 0 &&
        tmp->inventory.food == 0) {
            tmp->is_dead = true;
            event_pdi(server, tmp);
            continue;
        }
        if ((int)tmp->cycle_before_death - 1 <= 0) {
            tmp->inventory.food--;
            tmp->cycle_before_death = 120;
            event_pin(server, tmp);
            continue;
        }
        tmp->cycle_before_death--;
    }
}

static void eat(server_t *server)
{
    for (teams_t *tmp = server->teams; tmp != NULL; tmp = tmp->next)
        eat_per_teams(server, tmp);
}

void run_server(server_t *server)
{
    zappy_clock_t *clock = init_clock(server, server->frequency);


    init_server(server);
    add_client(server, server->poll.socket, LISTEN);
    for (int count = 0; !is_game_over(server); count++) {
        update_clock(clock);
        if (clock->accumulator < 1.0) {
            poll_func(server, clock);
            continue;
        }
        eat(server);
        player_cmd_execution(server);
        if (count % 20 == 0)
            map_update(server);
        while (clock->accumulator >= 1.0)
            clock->accumulator -= 1.0;
    }
    if (clock)
        free(clock);
}
