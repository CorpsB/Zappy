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
    {"forward", cmd_forward},
    {"right", cmd_right},
    {"left", cmd_left},
    {"take_object", cmd_take_object},
    {"set_object", cmd_set_object},
    {NULL, NULL}
};
