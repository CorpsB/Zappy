/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pdi.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pdi(server_t *server, player_t *player)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "pdi %d\n", player->id) == -1)
        logger(server, "PDI", ERROR, true);
    send_to_all_gui(server, buffer);
    if (buffer)
        free(buffer);
}

void event_pdi_by_index(void)
{
    //TO DO
    return;
}
