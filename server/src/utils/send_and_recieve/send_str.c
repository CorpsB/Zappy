/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** send_str
*/

/**
 * @file send_str.c
 * @brief Sends a complete message to a file descriptor, with optional
 * memory cleanup.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 *
 * @details
 * This file provides a utility function to send a string over a socket
 * or any file descriptor using `write`. It ensures the entire string is sent
 * even if `write` only writes part of it. It also handles optional memory
 * deallocation after the message is sent.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void send_str(server_t *server, int fd, char *message, bool need_free)
{
    int lenght = strlen(message);
    int tmp = 0;

    for (int i = 0; i < lenght;) {
        tmp = write(fd, message + i, lenght - i);
        if (tmp < 0)
            logger(server, "SEND : WRITE", PERROR, true);
        i += tmp;
    }
    if (need_free && message)
        free(message);
}
