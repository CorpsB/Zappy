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

const player_command_t player_command_table[] = {
    {"test", cmd_test, 1, 0},
    {"Forward", cmd_forward, 1, 7},
    {"Right", cmd_right, 1, 7},
    {"Left", cmd_left, 1, 7},
    {"Look", cmd_look, 1, 7},
    {"Inventory", cmd_inventory, 1, 1},
    {"Broadcast", cmd_broadcast_text, -1, 0},
    {"Connect_nbr", cmd_connect_nbr, 1, 0},
    {"Fork", cmd_fork, 1, 42},
    {"Eject", cmd_eject, 1, 7},
    {"Take", cmd_take_object, 2, 7},
    {"Set", cmd_set_object, 2, 7},
    {"Incantation", cmd_test, 1, 0},
    {NULL, NULL, 0, 0}
};

const gui_command_t gui_command_table[] = {
    {"msz", cmd_msz, 1},
    {"bct", cmd_bct, 3},
    {"mct", cmd_mct, 1},
    {"tna", cmd_tna, 1},
    {"ppo", cmd_ppo, 2},
    {"plv", cmd_plv, 2},
    {"pin", cmd_pin, 2},
    {"sgt", cmd_sgt, 1},
    {"sst", cmd_sst, 2},
    {NULL, NULL, 0}
};
