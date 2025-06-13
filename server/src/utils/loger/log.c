/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** log
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void need_stop(server_t *server, bool is_end)
{
    if (is_end) {
        logger(server, "END DUE TO LOGGER GOODBYE.", DEBUG, false);
        // free_server(server);
        exit(84);
    }
}

static void debug_logger(server_t *server, char *message, logs_t log)
{
    if (server->debug_fd == -1) {
        server->debug = false;
        logger(server, "IMPOSSIBLE OPEN", PERROR, true);
    }
    if (log == ERROR)
        dprintf(server->debug_fd, "[ERROR] - %s\n", message);
    if (log == PERROR)
        dprintf(server->debug_fd, "[ERROR] - %s: %s\n", message,
            strerror(errno));
    if (log == DEBUG)
        dprintf(server->debug_fd, "[DEBUG] - %s\n", message);
    if (log == INFO)
        dprintf(server->debug_fd, "[INFO] - %s\n", message);
}

void logger(server_t *server, char *message, logs_t log, bool is_end)
{
    if (log == ERROR)
        dprintf(2, "[ERROR] - %s\n", message);
    if (log == PERROR)
        dprintf(2, "[ERROR] - %s: %s\n", message, strerror(errno));
    if (log == DEBUG)
        dprintf(2, "[DEBUG] - %s\n", message);
    if (log == INFO)
        dprintf(2, "[INFO] - %s\n", message);
    if (server->debug)
        debug_logger(server, message, log);
    need_stop(server, is_end);
}
