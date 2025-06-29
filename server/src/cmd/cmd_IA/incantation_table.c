/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** incantation_table
*/

/**
 * @file incantation_table.c
 * @brief Defines the requirements for player incantations by level.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * Contains the constant array `requirement` specifying the number of players
 * and the quantities of each resource needed to perform an
 * incantation for each level.
 * This table is used by the server to validate and execute player level-ups.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/incantation_table.h"

const incantation_requirement_t requirement[] = {
    {1, 1, 0, 0, 0, 0, 0, 1},
    {2, 1, 1, 1, 0, 0, 0, 2},
    {3, 1, 0, 0, 0, 0, 0, 3},
    {4, 2, 0, 1, 0, 2, 0, 4},
    {5, 1, 1, 2, 0, 1, 0, 5},
    {6, 1, 2, 3, 0, 1, 0, 6},
    {7, 2, 2, 2, 2, 2, 1, 7},
};
