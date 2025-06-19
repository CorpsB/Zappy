/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** add_server
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

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
    return server;
}
