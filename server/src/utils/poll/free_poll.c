/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** free_poll
*/

/**
 * @file free_poll.c
 * @brief Cleanup functions related to the poll structure of the server.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 *
 * @details
 * This file provides a function to properly free and clean up all resources
 * associated with the poll system used for managing connected clients.
 *
 * It ensures:
 * - All client sockets are closed.
 * - Dynamically allocated memory for command buffers is freed.
 * - The arrays holding client and poll file descriptor structures are
 * released.
 *
 * This is typically called at server shutdown to avoid memory leaks or file
 * descriptor leaks.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

void free_poll(server_t *server)
{
    for (int i = 0; i < server->poll.connected_client; i++) {
        close(server->poll.pollfds[i].fd);
        if (server->poll.client_list[i].cmd)
            free(server->poll.client_list[i].cmd);
    }
    if (server->poll.client_list)
        free(server->poll.client_list);
    if (server->poll.pollfds)
        free(server->poll.pollfds);
}
