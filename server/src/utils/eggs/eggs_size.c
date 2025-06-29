/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** eggs_size
*/

/**
 * @file eggs_size.c
 * @brief Computes the number of eggs in a team's egg list.
 * @author Noé Carabin (CorpsB)
 * @version 1.0
 * @date 2025-06
 * @details
 * Provides a utility function that returns the size of the linked list of eggs
 * for a given team. Iterates through the list and counts the number of nodes.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

int eggs_size(eggs_t *eggs)
{
    int i = 0;

    if (!eggs || eggs == NULL)
        return 0;
    for (eggs_t *tmp = eggs; tmp != NULL; tmp = tmp->next)
        i++;
    return i;
}
