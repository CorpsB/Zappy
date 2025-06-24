/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** event_suc
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void event_suc(server_t *server, int index, char **args)
{
    dprintf(server->poll.pollfds[index].fd, "suc\n");
    logger(server, "UNKNOW GUI COMMAND:", INFO, false);
    logger(server, args[0], INFO, false);
}