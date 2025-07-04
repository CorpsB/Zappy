/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** search_eggs.c
*/

/**
 * @file search_eggs.c
 * @brief Provides functionality to search for an egg by its ID across all
 * teams.
 * @author Noé Carabin (CorpsB)
 * @version 1.0
 * @date 2025-06
 * @details
 * Implements a lookup mechanism to locate a specific egg by its unique
 * identifier. It traverses all teams and their respective egg lists,
 * returning the matching egg structure if found.
 */

#include "include/include.h"
#include "include/structure.h"

/**
 * @brief Search a specific egg by its id.
 *
 * @param eggs    Eggs structure pointer.
 * @param id      Id of the egg.
 *
 * @return        If the egg exist, return the egg else NULL.
 */
static eggs_t *find_eggs(eggs_t *eggs, unsigned int id)
{
    while (eggs) {
        if (eggs->id == id)
            return eggs;
        eggs = eggs->next;
    }
    return NULL;
}

eggs_t *search_egg_by_id(server_t *server, unsigned int id)
{
    teams_t *team;
    eggs_t *egg;

    if (!server)
        return NULL;
    team = server->teams;
    while (team) {
        egg = find_eggs(team->egg, id);
        if (egg)
            return egg;
        team = team->next;
    }
    return NULL;
}
