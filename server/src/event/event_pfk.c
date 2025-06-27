/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_pfk.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

eggs_t *create_egg_from_player(player_t *player)
{
    eggs_t *new_egg;

    if (!player || !player->team)
        return NULL;
    new_egg = malloc(sizeof(*new_egg));
    if (!new_egg)
        return NULL;
    new_egg->id = player->team->id * 1000 + rand() % 1000;
    new_egg->creator_id = player->id;
    new_egg->position[0] = player->position[0];
    new_egg->position[1] = player->position[1];
    new_egg->next = player->team->egg;
    player->team->egg = new_egg;
    return new_egg;
}

void event_pfk(server_t *server, player_t *player)
{
    char *buffer = NULL;
    eggs_t *egg;

    if (!server || !player)
        return;
    egg = create_egg_from_player(player);
    if (!egg)
        return;
    if (asprintf(&buffer, "pfk #%u", player->id) == -1)
        logger(server, "PFK", ERROR, true);
    send_to_all_gui(server, buffer);
    if (buffer)
        free(buffer);
    event_enw(server, player, egg);
}
