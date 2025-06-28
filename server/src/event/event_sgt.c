/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_sgt.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_sgt(server_t *server)
{
    char *buffer = NULL;

    if (!server)
        return;
    if (asprintf(&buffer, "sgt %u", server->frequency) == -1)
        logger(server, "SGT", ERROR, true);
    send_to_all_gui(server, buffer);
    if (buffer)
        free(buffer);
}
