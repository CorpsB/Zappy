/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** eggs_size
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