/*
** EPITECH PROJECT, 2025
** zappy – debug
** File description:
** Helpers to display the resources present on every map tile.
*/

/**
 * @file debug_print_resource_map.c
 * @brief Debug utilities to display the resources and their repartition
 * values on the map.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 *
 * @details
 * This file provides debugging utilities to inspect the in-game map's
 * resource distribution.
 * It displays, for each type of resource:
 * - the amount present on each tile of the map;
 * - the influence/repartition map used for spawning logic.
 *
 * Each resource is printed as a grid matching the map layout,
 * allowing visual confirmation
 * of both actual quantities and spread values.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/density_table.h"

/**
 * @brief Get the quantity of a specific resource on a tile.
 * @param tile The resources structure representing a single map tile.
 * @param type The type of resource to query (enum r_ressource_t).
 * @return unsigned int The quantity of the specified resource on the tile.
*/
static unsigned int get_resource_quantity(const resources_t tile,
    const r_ressource_t type)
{
    switch (type) {
        case FOOD:
            return tile.food;
        case LINEMATE:
            return tile.linemate;
        case DERAUMERE:
            return tile.deraumere;
        case SIBUR:
            return tile.sibur;
        case MENDIANE:
            return tile.mendiane;
        case PHIRAS:
            return tile.phiras;
        case THYSTAME:
            return tile.thystame;
        default:
            return 0;
    }
}

/**
 * @brief Print the quantity of a specific resource on each tile of the map.
 * This function iterates through the entire server map and prints
 * the quantity
 * of the specified resource for each tile in a formatted grid.
 * @param server Pointer to the server structure containing the map.
 * @param res_type The resource type to print (enum r_ressource_t).
*/
static void print_tile_quantity(const server_t *server,
    const r_ressource_t res_type)
{
    unsigned int qty;

    for (unsigned int y = 0; y < server->height; y++) {
        for (unsigned int x = 0; x < server->width; x++) {
            qty = get_resource_quantity(server->map[y][x], res_type);
            printf("[%2u] ", qty);
        }
        printf("\n");
    }
}

/**
 * @brief Print the repartition map values of a specific resource
 * across the server map.
 * The repartition map holds influence or weight values indicating
 * resource distribution.
 * This function prints these integer values in a grid format for
 * debugging purposes.
 * @param server Pointer to the server structure containing the map.
 * @param res_type The resource type to print from the repartition
 * map (enum r_ressource_t).
*/
static void print_repartition_map(const server_t *server,
    const r_ressource_t res_type)
{
    for (unsigned int y = 0; y < server->height; y++) {
        for (unsigned int x = 0; x < server->width; x++) {
            printf("[%2d] ",
                server->map[y][x].repartition_map[res_type]);
        }
        printf("\n");
    }
}

void debug_print_resource_map(server_t *server)
{
    for (r_ressource_t res_type = FOOD; res_type <= THYSTAME; res_type++) {
        if (printf("===== RESOURCE: %s =====\n",
            density_table[res_type].name) == -1)
            logger(server, "PRINTF", PERROR, true);
        print_tile_quantity(server, res_type);
        if (printf("\n--- Repartition Map (%s) ---\n",
            density_table[res_type].name) == -1)
            logger(server, "PRINTF", PERROR, true);
        print_repartition_map(server, res_type);
        if (printf("\n") == -1)
            logger(server, "PRINTF", PERROR, true);
    }
}
