/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_ppo.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_ppo(server_t *server, player_t *player)
{
    char *buffer = NULL;

    if (!server || !player || player->is_dead)
        return;
    if (asprintf(&buffer, "ppo #%u %u %u %u",
        player->id, player->position[0],
        player->position[1], player->direction) == -1)
        logger(server, "PPO", ERROR, true);
    send_to_all_gui(server, buffer);
}
