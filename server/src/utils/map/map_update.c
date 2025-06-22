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

static int search_map_information(server_t *server, r_ressource_t type,
    int *min)
{
    int size = 0;
    unsigned int j = 0;

    for (unsigned int i = 0; true; j++) {
        if (j >= server->width) {
            j = 0;
            i++;
        }
        if (i >= server->height)
            break;
        if (server->map[i][j].repartition_map[type] < *min) {
            *min = server->map[i][j].repartition_map[type];
            size = 1;
            continue;
        }
        if (*min == server->map[i][j].repartition_map[type])
            size++;
    }
    return size;
}

static void complete_table(server_t *server, r_ressource_t type, int min,
    int *table)
{
    int r_index = 0;
    unsigned int j = 0;

    for (unsigned int i = 0; true; j++) {
        if (j >= server->width) {
            j = 0;
            i++;
        }
        if (i >= server->height)
            break;
        if (server->map[i][j].repartition_map[type] == min) {
            table[r_index] = i;
            table[r_index + 1] = j;
            r_index += 2;
        }
    }
}

static void draw_circle(int *pos, r_ressource_t type, server_t *server, int *d)
{
    int x = pos[1] + d[0];
    int y = pos[0] + d[1];
    int dist;
    int influence;

    if (x < 0 || y < 0 || x >= (int)server->width || y >= (int)server->height)
        return;
    dist = abs(d[0]) + abs(d[1]);
    influence = d[2] - dist;
    if (influence <= 0)
        return;
    server->map[y][x].repartition_map[type] += influence;
}

//C'est un grand pas pour le coding-style, mais un petit pas pour continue;
void change_arround(server_t *srv, int *pos, r_ressource_t type, int weight)
{
    int r = weight;
    int dx = -r;
    int d[3];

    if (weight <= 0)
        return;
    d[2] = weight;
    for (int dy = -r; dy <= r; dx++) {
        if (dx > r) {
            dx = -r;
            dy++;
        }
        if (dy > r)
            break;
        d[0] = dy;
        d[1] = dx;
        draw_circle(pos, type, srv, d);
    }
}

static void spawn_ressource(server_t *server, r_ressource_t type,
    int *table, int size)
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

static void update_map_inventory(server_t *server, r_ressource_t type)
{
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
}

static void ressource_update(server_t *server, r_ressource_t type)
{
    int min = INT_MAX;
    int size = search_map_information(server, type, &min);
    int *table = malloc(sizeof(int) * (size * 2));

    if (!table)
        logger(server, "MALLOC", PERROR, true);
    update_map_inventory(server, type);
    complete_table(server, type, min, table);
    spawn_ressource(server, type, table, size);
    if (table)
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
    while (1) {
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
