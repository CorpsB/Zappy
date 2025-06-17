/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** parser_table
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/cmd.h"
#include "include/cmd_parser_table.h"

const command_t command_table1[] = {
    {"test", cmd_test},
    {"Forward", cmd_forward},
    {"Right", cmd_right},
    {"Left", cmd_left},
    {"Take object", cmd_take_object},
    {"Set object", cmd_set_object},
    {"Inventory", cmd_inventory},
    {"Eject", cmd_eject},
    {"Fork", cmd_fork},
    {"Connect_nbr", cmd_connect_nbr},
    {"msz", cmd_msz},
    {"bct", cmd_bct},
    {"mct", cmd_mct},
    {"tna", cmd_tna},
    {"ppo", cmd_ppo},
    {"plv", cmd_plv},
    {NULL, NULL}
};

const command_t command_table2[] = {
    {"pin", cmd_pin},
    {NULL, NULL}
};
