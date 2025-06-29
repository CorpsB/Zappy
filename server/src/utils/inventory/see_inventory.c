/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_inventory
*/

/**
 * @file see_inventory.c
 * @brief Displays the contents of a resource inventory to a given file
 * descriptor (typically for debugging purposes).
 * @author Noé Carabin (CorpsB)
 * @version 1.0
 * @date 2025-06
 * @details
 * Implements the `see_inventory()` function, which prints each type of
 * resource (food, linemate, deraumere, sibur, mendiane, phiras, thystame)
 * from a given `resources_t` structure to a specified file descriptor. This
 * is useful for monitoring players’ or tiles’ inventories during runtime.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void see_inventory(server_t *server, resources_t inv, int fd)
{
    if (dprintf(fd, "  Inventory:\n") == -1)
        logger(server, "DPRINTF", PERROR, true);
    if (dprintf(fd, "    Food      : %u\n", inv.food) == -1)
        logger(server, "DPRINTF", PERROR, true);
    if (dprintf(fd, "    Linemate  : %u\n", inv.linemate) == -1)
        logger(server, "DPRINTF", PERROR, true);
    if (dprintf(fd, "    Deraumere : %u\n", inv.deraumere) == -1)
        logger(server, "DPRINTF", PERROR, true);
    if (dprintf(fd, "    Sibur     : %u\n", inv.sibur) == -1)
        logger(server, "DPRINTF", PERROR, true);
    if (dprintf(fd, "    Mendiane  : %u\n", inv.mendiane) == -1)
        logger(server, "DPRINTF", PERROR, true);
    if (dprintf(fd, "    Phiras    : %u\n", inv.phiras) == -1)
        logger(server, "DPRINTF", PERROR, true);
    if (dprintf(fd, "    Thystame  : %u\n", inv.thystame) == -1)
        logger(server, "DPRINTF", PERROR, true);
}
