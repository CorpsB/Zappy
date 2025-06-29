/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** add_inventory
*/

/**
 * @file add_inventory.c
 * @brief Provides a utility function to initialize a resource inventory
 * with zero values.
 * @author Noé Carabin (CorpsB)
 * @version 1.0
 * @date 2025-06
 * @details
 * Defines the `create_resources()` function, which returns a `resources_t`
 * structure with all fields initialized to zero. This function is typically
 * used when initializing a new inventory for a player or a map tile.
 */


#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

resources_t create_resources(void)
{
    resources_t result;

    result.food = 0;
    result.deraumere = 0;
    result.linemate = 0;
    result.mendiane = 0;
    result.phiras = 0;
    result.sibur = 0;
    result.thystame = 0;
    return result;
}
