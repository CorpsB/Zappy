/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_eggs.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Print a single egg in one-line debug format.
 *
 * Utility used internally by see_eggs(); the caller guarantees @p egg
 * is non-NULL.
 *
 * @param egg Constant pointer to the #eggs_t structure to display.
 *
*/
static void see_one_egg(const eggs_t *egg)
{
    printf("\t[EGG] id=%u | creator=%u | pos=(%u,%u)\n",
        egg->id, egg->creator_id, egg->position[0], egg->position[1]);
}

void see_eggs(eggs_t *eggs)
{
    if (!eggs) {
        printf("\t\t[NO EGGS]\n");
        return;
    }
    printf("\t\t[EGGS]:\n");
    for (eggs_t *cur = eggs; cur; cur = cur->next)
        see_one_egg(cur);
}
