/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** free_eggs
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

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
