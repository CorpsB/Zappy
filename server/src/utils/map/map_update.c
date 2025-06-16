/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** map_update
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/density_table.h"

static void generate_food(server_t *server)
{
    while(server->actual_map_inventory.food < server->goal.food) {
        server->map[rand() % server->height][rand() % server->width].food++;
        server->actual_map_inventory.food++;
    }
}

void map_update(server_t *server)
{
    
}