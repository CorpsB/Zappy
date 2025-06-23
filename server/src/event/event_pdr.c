/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pdr
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pdr(server_t *server, int id, r_ressource_t type)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "pdr #%u %u", id, (int)type) == -1)
        logger(server, "PDR PER TILE", ERROR, true);
    send_to_all_gui(server, buffer);
    if (buffer)
        free(buffer);
}
