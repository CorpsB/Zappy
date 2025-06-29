/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** free_eggs
*/

/**
 * @file free_eggs.c
 * @brief Handles memory deallocation for egg structures in the server.
 * @author Noé Carabin (CorpsB)
 * @version 1.0
 * @date 2025-06
 * @details
 * Provides functions to free either a single egg or the entire linked list
 * of eggs associated with a team. Ensures proper cleanup to prevent memory
 * leaks.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Free a single egg structure.
 * @param egg Pointer to the egg to free.
*/
void free_a_egg(eggs_t *egg)
{
    if (egg)
        free(egg);
}

void free_all_egs(eggs_t *eggs)
{
    eggs_t *tmp;

    while (eggs) {
        tmp = eggs->next;
        free_a_egg(eggs);
        eggs = tmp;
    }
}
