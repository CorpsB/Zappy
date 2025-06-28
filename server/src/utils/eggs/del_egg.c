/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** del_egg
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Remove the first egg from a linked list.
 * @param tmp Current head of the list.
 * @param prv Unused, preserved for compatibility.
 * @param list Pointer to the head of the list (will be updated).
*/
void delete_first(eggs_t *tmp, eggs_t *prv, eggs_t **list)
{
    prv = tmp;
    tmp = tmp->next;
    if (prv)
        free(prv);
    *list = tmp;
}

void del_egg(server_t *, teams_t *teams, eggs_t *egg)
{
    eggs_t *prv = NULL;
    eggs_t *tmp = teams->egg;

    if (tmp == egg) {
        delete_first(tmp, prv, &teams->egg);
        return;
    }
    while (tmp != NULL) {
        if (tmp != egg) {
            prv = tmp;
            tmp = tmp->next;
            continue;
        }
        prv->next = tmp->next;
        if (tmp)
            free(tmp);
        return;
    }
}
