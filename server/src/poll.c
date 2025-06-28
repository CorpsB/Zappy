/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** poll
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Add a new client to the server's poll and client list.
 * @param server Pointer to the server structure.
 * @param socket Socket descriptor of the new client.
 * @param state Initial state of the client (UNKNOWN, PLAYER, GUI, etc.).
*/
static void add_client(server_t *serv, int socket, whoAmI_t state)
{
    serv->poll.pollfds = realloc(
        serv->poll.pollfds,
        sizeof(struct pollfd) * (serv->poll.connected_client + 1));
    serv->poll.client_list = realloc(
        serv->poll.client_list,
        sizeof(client_t) * (serv->poll.connected_client + 1));
    if (!serv->poll.pollfds || !serv->poll.client_list)
        logger(serv, "REALLOC", PERROR, true);
    serv->poll.pollfds[serv->poll.connected_client].fd = socket;
    serv->poll.pollfds[serv->poll.connected_client].events = POLLIN;
    serv->poll.pollfds[serv->poll.connected_client].revents = 0;
    serv->poll.client_list[serv->poll.connected_client].whoAmI = state;
    serv->poll.client_list[serv->poll.connected_client].player = NULL;
    serv->poll.client_list[serv->poll.connected_client].cmd = NULL;
    if (state == UNKNOWN)
        send_str(serv, serv->poll.pollfds[serv->poll.connected_client].fd,
            "WELCOME\n", false);
    serv->poll.client_index++;
    serv->poll.connected_client++;
    logger(serv, "NEW CLIENT", DEBUG, false);
    see_poll(serv->poll, 2, serv->poll.connected_client);
}

/**
 * @brief Check if a winning condition has been met.
 * Iterates through all teams to determine if a team has won the game.
 * @param server Pointer to the server structure.
 * @return true if the game is over, false otherwise.
*/
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

/**
 * @brief Remove a client from the server.
 * Closes the client's socket, triggers disconnection events, and shifts
 * the poll and client arrays to maintain consistency.
 * @param server Pointer to the server structure.
 * @param index Index of the client to remove.
 * @return true on success.
*/
static bool del_client(server_t *server, int index)
{
    close(server->poll.pollfds[index].fd);
    event_pdi_by_index(server, index);
    for (int i = 0; i < server->poll.connected_client; i++) {
        if (i > index) {
            server->poll.client_list[i - 1] = server->poll.client_list[i];
            server->poll.pollfds[i - 1] = server->poll.pollfds[i];
        }
    }
    server->poll.connected_client--;
    server->poll.client_list = realloc(server->poll.client_list,
        sizeof(client_t) * server->poll.connected_client);
    server->poll.pollfds = realloc(server->poll.pollfds,
        sizeof(struct pollfd) * server->poll.connected_client);
    if (!server->poll.pollfds || !server->poll.client_list)
        logger(server, "REALLOC", PERROR, true);
    return true;
}

/**
 * @brief Detect and handle incoming events on a client socket.
 * Accepts new connections or reads client commands, depending on the type
 * of client (LISTEN, PLAYER, GUI, etc.).
 * @param server Pointer to the server structure.
 * @param i Index of the client in the poll list.
 * @return true if an event was handled, false otherwise.
*/
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

/**
 * @brief Handle poll system call and process client events.
 * Waits for events on all client sockets and processes them if detected.
 * Uses the server's clock to determine the poll timeout.
 * @param server Pointer to the server structure.
 * @param clock Pointer to the server clock structure.
*/
static void poll_func(server_t *server, zappy_clock_t *clock)
{
    int event;
    int t = (unsigned int)
    ((1.0 - clock->accumulator) * 1000.0 / clock->freq);

    event = poll(server->poll.pollfds, server->poll.connected_client, (int)t);
    if (event == -1)
        logger(server, "POLL", PERROR, true);
    if (event == 0)
        return;
    for (int i = 0; i < server->poll.connected_client; i++) {
        if (event_detector(server, i))
            return;
    }
}

/**
 * @brief Handle food consumption and death for all players of a team.
 * Decreases the life cycle counter and food of each player.
 * If the player dies, triggers the appropriate event.
 * @param server Pointer to the server structure.
 * @param teams Pointer to the team structure.
*/
static void eat_per_teams(server_t *server, teams_t *teams)
{
    for (player_t *tmp = teams->player; tmp != NULL; tmp = tmp->next) {
        if (tmp->is_dead)
            continue;
        if ((int)tmp->cycle_before_death - 1 <= 0 &&
        tmp->inventory.food == 0) {
            tmp->is_dead = true;
            event_pdi(server, tmp, true);
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

/**
 * @brief Handle food consumption and death for all players in the game.
 * Calls eat_per_teams for each team.
 * @param server Pointer to the server structure.
*/
static void eat(server_t *server)
{
    for (teams_t *tmp = server->teams; tmp != NULL; tmp = tmp->next)
        eat_per_teams(server, tmp);
}

static void action_per_turn(server_t *server, int count)
{
    eat(server);
    player_cmd_execution(server);
    if (count % 20 == 0) {
        map_update(server);
        logger(server, "RESSOURCE ++", DEBUG, false);
    }
}

void run_server(server_t *server)
{
    zappy_clock_t *clock = init_clock(server, server->frequency);

    init_server(server);
    add_client(server, server->poll.socket, LISTEN);
    for (int count = 0; !is_game_over(server); count++) {
        update_clock(clock, server);
        if (clock->accumulator < 1.0) {
            poll_func(server, clock);
            continue;
        }
        action_per_turn(server, count);
        while (clock->accumulator >= 1.0)
            clock->accumulator -= 1.0;
    }
    if (clock)
        free(clock);
}
