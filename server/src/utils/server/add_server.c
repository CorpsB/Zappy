/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** add_server
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Initialize the main server socket and bind it.
 * This function creates the listening socket, configures its parameters,
 * binds it to the specified port, and starts listening for connections.
 * @param server Pointer to the server structure.
*/
void init_server(server_t *server)
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

/**
 * @brief Initialize/reset the server's actual map inventory
 * and poll structures.
 * Sets all resource counts in actual_map_inventory to zero and
 * initializes pollfds and client_list pointers to NULL.
 * @param server Pointer to the server structure to initialize.
*/
void server_actual_map(server_t *server)
{
    server->actual_map_inventory.food = 0;
    server->actual_map_inventory.linemate = 0;
    server->actual_map_inventory.deraumere = 0;
    server->actual_map_inventory.sibur = 0;
    server->actual_map_inventory.mendiane = 0;
    server->actual_map_inventory.phiras = 0;
    server->actual_map_inventory.thystame = 0;
    server->poll.pollfds = NULL;
    server->poll.client_list = NULL;
}

server_t *add_server(void)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server)
        logger(server, "MALLOC", PERROR, true);
    server->teams = NULL;
    server->map = NULL;
    server->teams_count = 0;
    server->starter_eggs_number = 0;
    server->frequency = 0;
    server->port = 0;
    server->height = 0;
    server->width = 0;
    server->eggs_count = 0;
    server->player_count = 0;
    server->debug = false;
    server->debug_fd = -1;
    server_actual_map(server);
    return server;
}
