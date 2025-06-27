/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_msz
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_msz(server_t *server)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "msz %u %u", server->width, server->height) == -1)
        logger(server, "MSZ", ERROR, true);
    send_to_all_gui(server, buffer);
    if (buffer)
        free(buffer);
}
