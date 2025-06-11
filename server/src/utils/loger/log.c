/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** log
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void log(server_t *server, char *message)
{
    write(2, message, strlen(message));
    if (server->debug_fd != -1) {
        write(server->debug_fd, message, strlen(message));
    } else {
        perror("[ERROR] - Debug option");
    }
}
