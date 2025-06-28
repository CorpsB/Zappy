/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_inventory
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void see_inventory(resources_t inv, int fd)
{
    dprintf(fd, "  Inventory:\n");
    dprintf(fd, "    Food      : %u\n", inv.food);
    dprintf(fd, "    Linemate  : %u\n", inv.linemate);
    dprintf(fd, "    Deraumere : %u\n", inv.deraumere);
    dprintf(fd, "    Sibur     : %u\n", inv.sibur);
    dprintf(fd, "    Mendiane  : %u\n", inv.mendiane);
    dprintf(fd, "    Phiras    : %u\n", inv.phiras);
    dprintf(fd, "    Thystame  : %u\n", inv.thystame);
}
