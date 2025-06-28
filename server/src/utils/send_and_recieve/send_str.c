/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** send_str
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void send_str(server_t *server, int fd, char *message)
{
    int lenght = strlen(message);
    int tmp = 0;

    for (int i = 0; i < lenght ;) {
        tmp = write(fd, message + i, lenght - i);
        if (tmp < 0)
            logger(server, "SEND : WRITE", PERROR, true);
        i += tmp;
    }
    if (message)
        free(message);
}
