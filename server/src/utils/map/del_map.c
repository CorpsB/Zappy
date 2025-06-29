/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** del_map
*/

/**
 * @file del_map.c
 * @brief Handles memory deallocation of dynamically allocated integer maps.
 * @author Noé Carabin (CorpsB)
 * @version 1.0
 * @date 2025-06
 * @details
 * Frees a two-dimensional integer map used in the Zappy server.
 * Iterates over the rows and deallocates them individually,
 * followed by the map pointer itself.
 * Prevents memory leaks during map regeneration or server shutdown.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void free_int_map(int y, int **map)
{
    while (y > 0) {
        free(map[y]);
        y--;
    }
    free(map);
}
