/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** log
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Free the server and exit the program if is_end is true.
 * @param server Pointer to the server structure.
 * @param is_end Boolean indicating whether to terminate the program.
*/
static void need_stop(server_t *server, bool is_end)
{
    if (is_end) {
        logger(server, "END DUE TO LOGGER GOODBYE.", DEBUG, false);
        free_server(server);
        exit(84);
    }
}

/**
 * @brief Write a log message to the debug log file based on the log level.
 * @param server Pointer to the server structure.
 * @param message The message to log.
 * @param log The log level (ERROR, PERROR, DEBUG, INFO).
*/
static void debug_logger(server_t *server, char *message, logs_t log)
{
    char *buffer = NULL;

    if (server->debug_fd == -1) {
        server->debug = false;
        logger(server, "IMPOSSIBLE OPEN", PERROR, true);
        return;
    }
    if (log == ERROR)
        asprintf(&buffer, "[ERROR] - %s\n", message);
    if (log == PERROR)
        asprintf(&buffer, "[ERROR] - %s: %s\n", message, strerror(errno));
    if (log == DEBUG)
        asprintf(&buffer, "[DEBUG] - %s\n", message);
    if (log == INFO)
        asprintf(&buffer, "[INFO] - %s\n", message);
    if (buffer)
        send_str(server, server->debug_fd, buffer, true);
}

void logger(server_t *server, char *message, logs_t log, bool is_end)
{
    char *buffer = NULL;

    if (log == ERROR)
        asprintf(&buffer, "[ERROR] - %s\n", message);
    if (log == PERROR)
        asprintf(&buffer, "[ERROR] - %s: %s\n", message, strerror(errno));
    if (log == DEBUG)
        asprintf(&buffer, "[DEBUG] - %s\n", message);
    if (log == INFO)
        asprintf(&buffer, "[INFO] - %s\n", message);
    if (buffer)
        write(2, buffer, strlen(buffer));
    if (server->debug)
        debug_logger(server, message, log);
    need_stop(server, is_end);
}
