/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** parse_teams
*/

/**
 * @file parse_teams.c
 * @brief Parses team names from command-line arguments and adds
 * them to the server.
 * @author Noé Carabin (CorpsB)
 * @version 1.0
 * @date 2025-06
 * @details
 * Extracts team names following the `-n` flag in the argument array.
 * Each team name is added to the server's team list until a new flag
 * (starting with '-') is encountered. Returns the index of the last
 * parsed argument.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

int parse_teams(char **av, server_t *server, int i)
{
    int j = i + 1;

    for (; av[j] && av[j][0] != '-'; j++)
        add_teams(server, av[j]);
    return j - 1;
}
