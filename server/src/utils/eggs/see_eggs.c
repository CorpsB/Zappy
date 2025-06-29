/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_eggs.c
*/

/**
 * @file see_eggs.c
 * @brief Displays all eggs of a team for debugging purposes using formatted
 * output.
 * @author Noé Carabin (CorpsB)
 * @version 1.0
 * @date 2025-06
 * @details
 * This module provides helper functions to print detailed information
 * about all eggs in a team's egg list to a file descriptor.
 * Used primarily for debugging and logging purposes to track egg data
 * such as ID, creator, and position.
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
static void see_one_egg(server_t *server, const eggs_t *egg, int fd)
{
    if (dprintf(fd, "\t[EGG] id=%u | creator=%u | pos=(%u,%u)\n",
        egg->id, egg->creator_id, egg->position[0], egg->position[1]) == -1)
        logger(server, "DPRINTF", PERROR, true);
}

void see_all_eggs(server_t *server, eggs_t *eggs, int fd)
{
    if (dprintf(fd, "[EGGS OF THE TEAM]\n") == -1)
        logger(server, "DPRINTF", PERROR, true);
    if (!eggs) {
        if (dprintf(fd, "\t[NO EGGS]\n") == -1)
            logger(server, "DPRINTF", PERROR, true);
        return;
    }
    if (dprintf(fd, "\t\t[EGGS]:\n") == -1)
        logger(server, "DPRINTF", PERROR, true);
    for (eggs_t *cur = eggs; cur; cur = cur->next)
        see_one_egg(server, cur, fd);
    if (dprintf(fd, "==============\n") == -1)
        logger(server, "DPRINTF", PERROR, true);
}
