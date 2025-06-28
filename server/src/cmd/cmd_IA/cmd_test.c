/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** test
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void cmd_test(server_t *server, int index, char **)
{
    dprintf(server->poll.pollfds[index].fd, "Jason a dit WALLAHHHHHHHHHHH\n");
}
