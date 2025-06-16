/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** map_generator
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/density_table.h"

static void define_actual_map_inventory(server_t *server)
{
    server->goal.food = 0;
    server->goal.linemate = 0;
    server->goal.deraumere = 0;
    server->goal.sibur = 0;
    server->goal.mendiane = 0;
    server->goal.phiras = 0;
    server->goal.thystame = 0;
}

static void define_goals(server_t *server)
{
    int map_size = server->width * server->height;

    server->goal.food = density_table[0].density * map_size;
    server->goal.linemate = density_table[1].density * map_size;
    server->goal.deraumere = density_table[2].density * map_size;
    server->goal.sibur = density_table[3].density * map_size;
    server->goal.mendiane = density_table[4].density * map_size;
    server->goal.phiras = density_table[5].density * map_size;
    server->goal.thystame = density_table[6].density * map_size;
}

void map_generator(server_t *server)
{
    server->map = malloc(sizeof(resources_t *) * server->height);
    server->map[server->height] = NULL;
    for(int i = 0; i < server->height; i++)
        server->map[i] = malloc(sizeof(resources_t) * server->width);
    define_actual_map_inventory(server);
    define_goals(server);
    map_update(server);
}
