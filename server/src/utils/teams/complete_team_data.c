/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** complete_team_data
*/

/**
 * @file complete_team_data.c
 * @brief Initializes the maximum slots for all teams.
 *
 * This file provides functionality to update all teams in the server
 * with the correct number of maximum slots, based on the server’s
 * configured number of starter eggs.
 *
 * @author Noé Carabin
 * @date 2025
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void complete_team_data(server_t *server)
{
    for (teams_t *tmp = server->teams; tmp != NULL; tmp = tmp->next)
        tmp->slots_max = server->starter_eggs_number;
}
