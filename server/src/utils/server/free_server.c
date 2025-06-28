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
 * @brief Free memory allocated for a single map unit.
 * @param map Pointer to the resources_t structure representing a map tile.
*/
static void free_map_unit(resources_t *map)
{
    if (map)
        free(map);
}

/**
 * @brief Free the entire map grid.
 * Frees each allocated map unit in the 2D map array.
 * @param server Pointer to the server structure containing map dimensions.
 * @param map 2D array of resources_t pointers representing the map.
*/
static void free_map(server_t *server, resources_t **map)
{
    return;
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
    free_poll(server);
    free(server);
}
