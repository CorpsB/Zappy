/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** see_inventory
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void see_inventory(resources_t inv)
{
    dprintf(2, "  Inventory:\n");
    dprintf(2, "    Food      : %u\n", inv.food);
    dprintf(2, "    Linemate  : %u\n", inv.linemate);
    dprintf(2, "    Deraumere : %u\n", inv.deraumere);
    dprintf(2, "    Sibur     : %u\n", inv.sibur);
    dprintf(2, "    Mendiane  : %u\n", inv.mendiane);
    dprintf(2, "    Phiras    : %u\n", inv.phiras);
    dprintf(2, "    Thystame  : %u\n", inv.thystame);
}
