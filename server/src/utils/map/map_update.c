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

static void complete_line_h(server_t *server, int *pos, r_ressource_t type, int weight)
{
    for (int i = 0; i < pos[2]; i++) {
        if (pos[0] < 0 || i + pos[1] < 0 ||
            pos[0] > (int)server->height - 1 || i + pos[1] > (int)server->width - 1)
            continue;
        server->map[pos[0]][i + pos[1]].repartition_map[type] += weight;
    }
}

static void complete_line_v(server_t *server, int *pos, r_ressource_t type, int weight)
{
    for (int i = 0; i < pos[2]; i++) {
        if (pos[1] < 0 || i + pos[0] < 0 ||
            pos[1] > (int)server->width - 1 || i + pos[0] > (int)server->height - 1)
            continue;
        server->map[pos[0] + i][pos[1]].repartition_map[type] += weight;
    }
}

void change_arround(server_t *server, int *pos, r_ressource_t type, int weight)
{
    int r = density_table[type].repartition_value - weight + 1;
    int line_len = r * 2 + 1;
    int pos_ht[3] = {pos[0] - r, pos[1] - r, line_len};
    int pos_hb[3] = {pos[0] + r, pos[1] - r, line_len};
    int pos_vl[3] = {pos[0] - r + 1, pos[1] - r, line_len - 2};
    int pos_vr[3] = {pos[0] - r + 1, pos[1] + r, line_len - 2};

    if (weight == 0 || pos[0] < 0 || pos[1] < 0 ||
        pos[0] > (int)server->height - 1 || pos[1] > (int)server->width - 1)
        return;
    complete_line_v(server, pos_vl, type, weight);
    complete_line_v(server, pos_vr, type, weight);
    complete_line_h(server, pos_ht, type, weight);
    complete_line_h(server, pos_hb, type, weight);
    if (weight > 0)
        change_arround(server, pos, type, weight - 1);
    else
        change_arround(server, pos, type, weight + 1);
}

static void sapwn_ressource(server_t *server, r_ressource_t type, int *table, int size)
{
    int r = rand() % size;
    int pos[2] = {table[r], table[r + 1]};
    int weight = density_table[type].repartition_value;

    server->map[pos[0]][pos[1]].repartition_map[type] += weight;
    change_arround(server, pos, type, weight - 1);
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

    complete_table(server, type, min, table);
    sapwn_ressource(server, type, table, size);
}

static bool is_update_complete(server_t *server)
{
    if (server->actual_map_inventory.food == server->goal.food &&
        server->actual_map_inventory.linemate == server->goal.linemate &&
        server->actual_map_inventory.deraumere == server->goal.deraumere &&
        server->actual_map_inventory.sibur == server->goal.sibur &&
        server->actual_map_inventory.mendiane == server->goal.mendiane &&
        server->actual_map_inventory.phiras == server->goal.phiras &&
        server->actual_map_inventory.thystame == server->goal.thystame)
        return true;
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
        if (is_update_complete(server))
            break;
    }
}