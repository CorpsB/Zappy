/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** free_server
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void free_map_unit(resources_t *map)
{
    if (map)
        free(map);
}

static void free_map(server_t *server, resources_t **map)
{
    for (unsigned int x = 0; x < server->height; x++) {
        for (unsigned int y = 0; y < server->height; y++) {
            free_map_unit(&map[x][y]);
        }
    }
}

void free_server(server_t *server)
{
    if (!server)
        return;
    free_map(server, server->map);
    free_all_teams(server->teams);
    free(server);
}
