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

static void init_rapartition_cells(server_t *server)
{
    for (unsigned int i = 0; i < server->height; i++) {
        for (unsigned int j = 0; j < server->width; j++) {
            server->map[i][j].repartition_map[FOOD] = 0;
            server->map[i][j].repartition_map[LINEMATE] = 0;
            server->map[i][j].repartition_map[DERAUMERE] = 0;
            server->map[i][j].repartition_map[SIBUR] = 0;
            server->map[i][j].repartition_map[MENDIANE] = 0;
            server->map[i][j].repartition_map[THYSTAME] = 0;
        }
    }
}

static void spawn_eggs(server_t *server)
{
    for (teams_t *tmp = server->teams; tmp != NULL; tmp = tmp->next)
        while ((unsigned int)eggs_size(tmp->egg) < server->starter_eggs_number)
            generate_starter_eggs(server, tmp);
}

void map_generator(server_t *server)
{
    server->map = malloc(sizeof(resources_t *) * (server->height + 1));
    if (!server->map)
        logger(server, "MALLOC", PERROR, true);
    server->map[server->height] = NULL;
    for (unsigned int i = 0; i < server->height; i++) {
        server->map[i] = malloc(sizeof(resources_t) * server->width);
        if (!server->map[i])
            logger(server, "MALLOC", PERROR, true);
        for (unsigned int j = 0; j < server->width; j++)
            memset(&server->map[i][j], 0, sizeof(resources_t));
    }
    define_actual_map_inventory(server);
    define_goals(server);
    init_rapartition_cells(server);
    map_update(server);
    spawn_eggs(server);
}
