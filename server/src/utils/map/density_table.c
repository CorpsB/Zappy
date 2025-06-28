/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** ressources
*/

#include "include/density_table.h"

/**
 * @brief Resource density and influence table.
 * This table defines:
 * - The density ratio for each resource type.
 * - The influence weight used in the resource repartition map.
 * Used to control how frequently resources appear on the map and
 * their spread.
*/
const density_t density_table[] = {
    {"food", 0.5, 2},
    {"linemate", 0.3, 3},
    {"deraumere", 0.15, 4},
    {"sibur", 0.1, 5},
    {"mendiane", 0.1, 5},
    {"phiras", 0.08, 6},
    {"thystame", 0.05, 7},
    {"", 0, 0}
};
