/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** free_server
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Free the entire map grid.
 * Frees each allocated map unit in the 2D map array.
 * @param server Pointer to the server structure containing map dimensions.
 * @param map 2D array of resources_t pointers representing the map.
*/
static void free_map(server_t *server, resources_t **map)
{
    for (unsigned int i = 0; i < server->height; i++)
        free(map[i]);
    free(map);
}

void free_server(server_t *server)
{
    if (!server)
        return;
    if (server->clock)
        free(server->clock);
    free_map(server, server->map);
    free_all_teams(server->teams);
    free_poll(server);
    free(server);
}
