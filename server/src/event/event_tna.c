/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_tna.c
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
        if (asprintf(&buffer, "tna %s\n", team->name) == -1)
            logger(server, "TNA", ERROR, true);
        send_to_all_gui(server, buffer);
        if (buffer)
            free(buffer);
        team = team->next;
    }
}
