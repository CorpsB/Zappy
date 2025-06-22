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

const command_t command_table[] = {
    {"test", cmd_test, 0},
    {"Forward", cmd_forward, 7},
    {"Right", cmd_right, 7},
    {"Left", cmd_left, 7},
    {"Take object", cmd_take_object, 7},
    {"Set object", cmd_set_object, 7},
    {"Inventory", cmd_inventory, 1},
    {"Eject", cmd_eject, 7},
    {"Fork", cmd_fork, 42},
    {"Connect_nbr", cmd_connect_nbr, 0},
    {"msz", cmd_msz, 0},
    {"bct", cmd_bct, 0},
    {"mct", cmd_mct, 0},
    {"tna", cmd_tna, 0},
    {"ppo", cmd_ppo, 0},
    {"plv", cmd_plv, 0},
    {"pin", cmd_pin, 0},
    {"sst", cmd_sst, 0},
    {"sgt", cmd_sgt, 0},
    {NULL, NULL, 0}
};
