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

static int search_map_information(server_t *server, r_ressource_t type, int *min)
{
    int size = 0;

    for (unsigned int i = 0; i < server->height; i++) {
        for (unsigned int j = 0; j < server->width; j++) {
            if (server->map[i][j].repartition_map[type] < *min) {
                *min = server->map[i][j].repartition_map[type];
                size = 1;
                continue;
            }
            if (*min == server->map[i][j].repartition_map[type])
                size++;
        }
    }
    printf("Min found for %i type is %i\n", type, *min);
    return size;
}

static void complete_table(server_t *server, r_ressource_t type, int min, int *table)
{
    int r_index = 0;

    for (unsigned int i = 0; i < server->height; i++) {
        for (unsigned int j = 0; j < server->width; j++) {
            if (server->map[i][j].repartition_map[type] == min) {
                table[r_index] = i;
                table[r_index + 1] = j;
                r_index += 2;
            }
        }
    }
}

void change_arround(server_t *srv, int *pos, r_ressource_t type, int weight)
{
    if (weight <= 0) return;
    int r = weight;

    for (int dy = -r; dy <= r; dy++)
        for (int dx = -r; dx <= r; dx++) {
            int x = pos[1] + dx, y = pos[0] + dy;
            if (x < 0 || y < 0 || x >= (int)srv->width || y >= (int)srv->height)
                continue;
            int dist = abs(dx) + abs(dy);
            int influence = weight - dist;
            if (influence <= 0) continue;
            srv->map[y][x].repartition_map[type] += influence;
        }
}

static void sapwn_ressource(server_t *server, r_ressource_t type, int *table, int size)
{
    int r = rand() % size;
    int pos[2] = {table[r * 2], table[r * 2 + 1]};
    int weight = density_table[type].repartition_value;

    server->map[pos[0]][pos[1]].repartition_map[type] += weight;
    change_arround(server, pos, type, weight - 1);
    if (type == FOOD)
        server->map[pos[0]][pos[1]].food++;
    if (type == LINEMATE)
        server->map[pos[0]][pos[1]].linemate++;
    if (type == DERAUMERE)
        server->map[pos[0]][pos[1]].deraumere++;
    if (type == SIBUR)
        server->map[pos[0]][pos[1]].sibur++;
    if (type == MENDIANE)
        server->map[pos[0]][pos[1]].mendiane++;
    if (type == PHIRAS)
        server->map[pos[0]][pos[1]].phiras++;
    if (type == THYSTAME)
        server->map[pos[0]][pos[1]].thystame++;
}

static void ressource_update(server_t *server, r_ressource_t type)
{
    int min = INT_MAX;
    int size = search_map_information(server, type, &min);
    int *table = malloc(sizeof(int) * (size * 2));

    if (type == FOOD)
        server->actual_map_inventory.food++;
    if (type == LINEMATE)
        server->actual_map_inventory.linemate++;
    if (type == DERAUMERE)
        server->actual_map_inventory.deraumere++;
    if (type == SIBUR)
        server->actual_map_inventory.sibur++;
    if (type == MENDIANE)
        server->actual_map_inventory.mendiane++;
    if (type == PHIRAS)
        server->actual_map_inventory.phiras++;
    if (type == THYSTAME)
        server->actual_map_inventory.thystame++;
    complete_table(server, type, min, table);
    sapwn_ressource(server, type, table, size);
    free(table);
}

static bool is_update_complete(server_t *server)
{
    if (server->actual_map_inventory.food == server->goal.food &&
        server->actual_map_inventory.linemate == server->goal.linemate &&
        server->actual_map_inventory.deraumere == server->goal.deraumere &&
        server->actual_map_inventory.sibur == server->goal.sibur &&
        server->actual_map_inventory.mendiane == server->goal.mendiane &&
        server->actual_map_inventory.phiras == server->goal.phiras &&
        server->actual_map_inventory.thystame == server->goal.thystame) {
        return true;
        }
    return false;
}

void map_update(server_t *server)
{
    while(1) {
        if (server->actual_map_inventory.food < server->goal.food)
            ressource_update(server, FOOD);
        if (server->actual_map_inventory.linemate < server->goal.linemate)
            ressource_update(server, LINEMATE);
        if (server->actual_map_inventory.deraumere < server->goal.deraumere)
            ressource_update(server, DERAUMERE);
        if (server->actual_map_inventory.sibur < server->goal.sibur)
            ressource_update(server, SIBUR);
        if (server->actual_map_inventory.mendiane < server->goal.mendiane)
            ressource_update(server, MENDIANE);
        if (server->actual_map_inventory.phiras < server->goal.phiras)
            ressource_update(server, PHIRAS);
        if (server->actual_map_inventory.thystame < server->goal.thystame)
            ressource_update(server, THYSTAME);
        if (is_update_complete(server))
            break;
    }
}