/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_inventory
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
