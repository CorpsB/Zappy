/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_mct.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"


//ICI LA VRAI COMMANDE MCT JUSTE SUPPR CELLE DU DESSOUS ET DECOM CELLE Là ET FONCTION IMPLEMENTER
// void cmd_mct(server_t *server, int index, char **args)
// {
//     int fd;
//     const resources_t *tile;

//     (void)args;
//     if (!server || !server->poll.client_list || index < 0 ||
//         index >= server->poll.client_index)
//         return;
//     if (check_graphical(server, index) != 0)
//         return;
//     fd = server->poll.pollfds[index].fd;
//     for (unsigned y = 0; y < server->height; y++) {
//         for (unsigned x = 0; x < server->width; x++) {
//             tile = &server->map[y][x];
//             dprintf(fd, "bct %u %u %u %u %u %u %u %u %u\n",
//                 x, y, tile->food, tile->linemate, tile->deraumere,
//                 tile->sibur, tile->mendiane, tile->phiras, tile->thystame);
//         }
//     }
// }

//CI DESSOUS LA VERSION DE TEST SANS LA MAP
void cmd_mct(server_t *server, int index, char **args)
{
    int fd;

    (void)args;
    if (!server || !server->poll.client_list || index < 0 ||
        index >= server->poll.client_index)
        return;
    if (check_graphical(server, index) != 0)
        return;

    fd = server->poll.pollfds[index].fd;

    for (unsigned y = 0; y < server->height; y++) {
        for (unsigned x = 0; x < server->width; x++) {
            dprintf(fd, "bct %u %u 0 0 0 0 0 0 0\n", x, y);
        }
    }
}