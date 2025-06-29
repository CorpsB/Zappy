/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** cmd_broadcast_text3.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

bool check_sender(player_t *snd)
{
    return (!snd || snd->is_dead);
}

bool is_valid_rcv(server_t *srv, player_t *rcv, player_t *snd, int i)
{
    return (srv->poll.client_list[i].whoAmI == PLAYER &&
        rcv && rcv != snd && !rcv->is_dead);
}
