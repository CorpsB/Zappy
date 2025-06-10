/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_server
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void see_server(server_t *server)
{
    if (!server) {
        printf("[DEBUG] - SEE SERVER : (null pointer)\n");
        return;
    }
    printf("[DEBUG] - SEE SERVER :\n\n");
    printf(" > Port : %u\n", server->port);
    printf(" > Map size : %ux%u\n", server->width, server->height);
    printf(" > Frequency : %u ticks/sec\n", server->frequency);
    printf(" > Max clients per team : %u\n", server->max_connections_per_team);
    printf(" > Total teams : %u\n", server->teams_count);
    printf(" > Total players : %u\n", server->player_count);
    printf(" > Total eggs : %u\n", server->eggs_count);
    printf(" > Map pointer : %s\n", server->map ? "initialized" : "NULL");
    printf(" > Teams pointer : %s\n", server->teams ? "initialized" : "NULL");
    see_teams(server->teams);
}
