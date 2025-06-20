/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_map
*/

#include "include/structure.h"
#include "include/density_table.h"
#include <stdio.h>

static const char *resource_names[] = {
    "FOOD", "LINEMATE", "DERAUMERE", "SIBUR",
    "MENDIANE", "PHIRAS", "THYSTAME"
};

static unsigned int get_resource_quantity(resources_t tile, r_ressource_t type)
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

void debug_print_resource_map(server_t *server)
{
    for (int type = 0; type <= THYSTAME; type++) {
        printf("===== RESOURCE: %s =====\n", resource_names[type]);

        for (unsigned int y = 0; y < server->height; y++) {
            for (unsigned int x = 0; x < server->width; x++) {
                unsigned int qty = get_resource_quantity(server->map[y][x], type);
                printf("[%2u] ", qty);
            }
            printf("\n");
        }

        printf("\n--- Repartition Map (%s) ---\n", resource_names[type]);

        for (unsigned int y = 0; y < server->height; y++) {
            for (unsigned int x = 0; x < server->width; x++) {
                printf("[%2d] ", server->map[y][x].repartition_map[type]);
            }
            printf("\n");
        }
        printf("\n\n");
    }
}
