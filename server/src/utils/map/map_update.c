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

static int search_map_information(server_t *server, r_ressource_t type, int *min)
{
    int size = 0;

    for (int i = 0; i < server->height; i++) {
        for (int j = 0; j < server->width; j++) {
            if (*min < server->map[i][j].repartition_map[type]) {
                *min = server->map[i][j].repartition_map[type];
                size = 1;
                continue;
            }
            if (*min == server->map[i][j].repartition_map[type])
                size++;
        }
    }
    return size;
}

static void complete_table(server_t *server, r_ressource_t type, int min, int *table)
{
    int r_index = 0;

    for (int i = 0; i < server->height; i++) {
        for (int j = 0; j < server->width; j++) {
            if (server->map[i][j].repartition_map[type] == min) {
                table[r_index] = i;
                table[r_index + 1] = j;
                r_index += 2;
            }
        }
    }
}

static void complete_line_h(server_t *server, int *pos, r_ressource_t type, int weight)
{
    for (int i = 0; i < pos[2]; i++) {
        if (pos[0] <= 0 || i + pos[1] <= 0 ||
            pos[0] >= server->height - 1 || i + pos[1] >= server->width - 1)
            continue;
        server->map[pos[0]][i + pos[1]].repartition_map[type] += weight;
    }
}

static void complete_line_v(server_t *server, int *pos, r_ressource_t type, int weight)
{
    for (int i = 0; i < pos[2]; i++) {
        if (pos[1] <= 0 || i + pos[0] <= 0 ||
            pos[1] >= server->width - 1 || i + pos[0] >= server->height - 1)
            continue;
        server->map[pos[0] + i][pos[1]].repartition_map[type] += weight;
    }
}

void change_arround(server_t *server, int *pos, r_ressource_t type, int weight)
{
    int ragnar = density_table[type].repartition_value - weight + 1;
    int pos_h[3] = {pos[0] - ragnar, pos[1] - ragnar, ragnar * 2 + 1};
    int pos_v[3] = {pos[0] - ragnar - 1, pos[1] - ragnar, ragnar * 2 - 1};

    if (weight == 0 || pos[0] <= 0 || pos[1] <= 0 ||
        pos[0] >= server->height - 1 || pos[1] >= server->width - 1)
        return;
    complete_line_v(server, pos_v, type, weight);
    complete_line_h(server, pos_h, type, weight);
    change_arround(server, pos, type, weight - 1);
}

static void sapwn_ressource(server_t *server, r_ressource_t type, int *table, int size)
{
    int r = rand() % size;
    int pos[2] = {table[r], table[r + 1]};
    int weight = density_table[type].repartition_value;

    change_arroud(server, pos, type);
    if (type == FOOD)
        server->map[table[r]][table[r + 1]].food++;
    if (type == LINEMATE)
        server->map[table[r]][table[r + 1]].linemate++;
    if (type == DERAUMERE)
        server->map[table[r]][table[r + 1]].deraumere++;
    if (type == SIBUR)
        server->map[table[r]][table[r + 1]].sibur++;
    if (type == MENDIANE)
        server->map[table[r]][table[r + 1]].mendiane++;
    if (type == PHIRAS)
        server->map[table[r]][table[r + 1]].phiras++;
    if (type == THYSTAME)
        server->map[table[r]][table[r + 1]].thystame++;
}

static void ressource_update(server_t *server, r_ressource_t type)
{
    int min = INT_MAX;
    int size = search_map_information(server, type, &min);
    int *table = malloc(sizeof(int) * (size * 2));

    complete_table(table, type, min, table);
    spawn_ressource(server, type);
}

void map_update(server_t *server)
{
    while(1) {
        if (server->actual_map_inventory.food < server->goal.food)
            ressource_update(server, FOOD);
        if (server->actual_map_inventory.food < server->goal.food)
            ressource_update(server, FOOD);
        if (server->actual_map_inventory.food < server->goal.food)
            ressource_update(server, FOOD);
        if (server->actual_map_inventory.food < server->goal.food)
            ressource_update(server, FOOD);
        if (server->actual_map_inventory.food < server->goal.food)
            ressource_update(server, FOOD);
        if (server->actual_map_inventory.food < server->goal.food)
            ressource_update(server, FOOD);
        if (server->actual_map_inventory.food < server->goal.food)
            ressource_update(server, FOOD);
        if (server->actual_map_inventory.food == server->goal.food &&
            server->actual_map_inventory.food == server->goal.food &&
            server->actual_map_inventory.food == server->goal.food &&
            server->actual_map_inventory.food == server->goal.food &&
            server->actual_map_inventory.food == server->goal.food &&
            server->actual_map_inventory.food == server->goal.food &&
            server->actual_map_inventory.food == server->goal.food)
            break;
    }
}