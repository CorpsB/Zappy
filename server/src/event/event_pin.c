/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pin.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_pin(server_t *server, player_t *player)
{
    char *buffer = NULL;

    if (!server || !player || player->is_dead)
        return;
    if (asprintf(&buffer,
        "pin #%u %u %u %u %u %u %u %u %u %u",
        player->id, player->position[0], player->position[1],
        player->inventory.food, player->inventory.linemate,
        player->inventory.deraumere, player->inventory.sibur,
        player->inventory.mendiane, player->inventory.phiras,
        player->inventory.thystame) == -1)
        logger(server, "PIN", ERROR, true);
    send_to_all_gui(server, buffer);
    if (buffer)
        free(buffer);
}
