/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_edi.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_edi(server_t *server, unsigned int egg_id)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "edi #%u", egg_id) == -1)
            logger(server, "EDI", ERROR, true);
        send_to_all_gui(server, buffer);
        if (buffer)
            free(buffer);
}
