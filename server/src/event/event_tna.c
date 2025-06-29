/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_tna.c
*/

/**
 * @file event_tna.c
 * @brief Implements the team names notification event ("tna")
 * for graphical clients.
 * Provides the list of all registered teams in the game to GUI clients,
 * typically sent when a new graphical client connects.
 * @author Thibaut Louis
 * @version 1.0
 * @date 2025-06
 * @details
 * Sends a "tna" message for each existing team to all GUI clients,
 * containing the team's name.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_tna(server_t *server)
{
    teams_t *team = NULL;
    char *buffer = NULL;

    if (!server || !server->teams)
        return;
    team = server->teams;
    while (team) {
        if (asprintf(&buffer, "tna %s", team->name) == -1)
            logger(server, "TNA", ERROR, true);
        send_to_all_gui(server, buffer);
        team = team->next;
    }
}
