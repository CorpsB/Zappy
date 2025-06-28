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

/**
 * @brief Searches the map to find the minimum repartition value for a
 * given resource and counts how many cells have it.
 * Iterates through the map cells and updates the minimum repartition
 * value found.
 * Counts the number of cells that have this minimum value.
 * @param server Pointer to the server containing the map.
 * @param type Resource type to search repartition for.
 * @param min Pointer to an integer holding the minimum repartition value;
 * updated by the function.
 * @return int Number of cells having the minimum repartition value.
*/
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

/**
 * @brief Completes an integer table with coordinates of map cells
 * matching a specific repartition value.
 * Fills the provided table with pairs of coordinates (row, column)
 * for all cells
 * where the repartition map value for the resource equals 'min'.
 * @param server Pointer to the server containing the map.
 * @param type Resource type for which cells are searched.
 * @param min The repartition value to match.
 * @param table Pre-allocated integer array to store the coordinates.
 * Must be large enough.
*/
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

/**
 * @brief Increases repartition influence on map cells within a weighted
 * "circle" around a position.
 * Applies a diminishing influence based on Manhattan distance
 * around the position,
 * updating the repartition_map values accordingly.
 * @param pos Array of two integers representing the position [row, column].
 * @param type Resource type to update.
 * @param server Pointer to the server containing the map.
 * @param d Array of three integers: d[0] and d[1] are offsets, d[2] is the
 * maximum influence (weight).
*/
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

static void add_ressources_on_map(server_t *server, r_ressource_t type,
    int *pos)
{
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

/**
 * @brief Spawns a resource on the map at one of the least occupied cells.
 * Selects a random position from cells with minimum repartition value and
 * increments resource counts both in repartition_map and the resource field
 * for that cell. Also updates nearby cells' repartition with
 * decreasing influence.
 * @param server Pointer to the server containing the map.
 * @param type Resource type to spawn.
 * @param table Array of coordinates for candidate cells.
 * @param size Number of candidate cells (pairs of coordinates).
*/
static void spawn_ressource(server_t *server, r_ressource_t type,
    int *table, int size)
{
    int r = rand() % size;
    int pos[2] = {table[r * 2], table[r * 2 + 1]};
    int weight = density_table[type].repartition_value;

    server->map[pos[0]][pos[1]].repartition_map[type] += weight;
    change_arround(server, pos, type, weight - 1);
    add_ressources_on_map(server, type, pos);
    event_bct_per_tile(server, pos[0], pos[1]);
}

/**
 * @brief Updates the server's actual map inventory count for a given
 * resource.
 * Increments the count of the specified resource in the actual_map_inventory.
 * @param server Pointer to the server whose inventory is updated.
 * @param type Resource type to update.
*/
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

/**
 * @brief Performs the update process for a specific resource on the map.
 * Searches cells with minimum repartition, updates the inventory, completes
 * coordinate table and spawns a resource in a chosen cell.
 * @param server Pointer to the server containing the map.
 * @param type Resource type to update.
*/
static void ressource_update(server_t *server, r_ressource_t type)
{
    int min = INT_MAX;
    int size = search_map_information(server, type, &min);
    int *table = malloc(sizeof(int) * (size * 2));

    logger(server, "RELOAD", DEBUG, false);
    if (!table)
        logger(server, "MALLOC", PERROR, true);
    update_map_inventory(server, type);
    complete_table(server, type, min, table);
    spawn_ressource(server, type, table, size);
    if (table)
        free(table);
}

/**
 * @brief Checks whether the actual inventory matches the goal
 * inventory for all resources.
 * Compares current actual_map_inventory and goal resource counts.
 * @param server Pointer to the server whose inventory is checked.
 * @return true if all resource counts match their goals; false otherwise.
*/
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
