/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_smg
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_smg(server_t *server, char *name)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "SMG %s", name) == -1)
        logger(server, "SMG", ERROR, true);
    send_to_all_gui(server, buffer);
    if (buffer)
        free(buffer);
}
