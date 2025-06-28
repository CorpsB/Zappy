/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** del_map
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
