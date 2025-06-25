/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** del_map
*/

void free_map(int y, int **map)
{
    while (y > 0) {
        free(map[y]);
        y--;
    }
    free(map);
}
