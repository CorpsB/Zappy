/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pgt
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pgt(server_t *server, int id, r_ressource_t type)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "pgt #%u %u", id, (int)type) == -1)
        logger(server, "PGT PER TILE", ERROR, true);
    send_to_all_gui(server, buffer);
}
