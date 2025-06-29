/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** log
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void emergency_end(server_t *server)
{
    write(2, "[EMERGENCY END] - Cannot use logger func.\n", 42);
    free_server(server);
    exit(84);
}

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
        if (asprintf(&buffer, "[ERROR] - %s\n", message) == -1)
            emergency_end(server);
    if (log == PERROR)
        if (asprintf(&buffer, "[ERROR] - %s: %s\n", message, strerror(errno)) == -1)
            emergency_end(server);
    if (log == DEBUG)
        if (asprintf(&buffer, "[DEBUG] - %s\n", message) == -1)
            emergency_end(server);
    if (log == INFO)
        if (asprintf(&buffer, "[INFO] - %s\n", message) == -1)
            emergency_end(server);
    if (buffer)
        dprintf(server->debug_fd, "%s\n", buffer);
}


void logger(server_t *server, char *message, logs_t log, bool is_end)
{
    char *buffer = NULL;

    if (log == ERROR)
        if (asprintf(&buffer, "[ERROR] - %s\n", message) == -1)
            emergency_end(server);
    if (log == PERROR)
        if (asprintf(&buffer, "[ERROR] - %s: %s\n", message, strerror(errno)) == -1)
            emergency_end(server);
    if (log == DEBUG)
        if (asprintf(&buffer, "[DEBUG] - %s\n", message) == -1)
            emergency_end(server);
    if (log == INFO)
        if (asprintf(&buffer, "[INFO] - %s\n", message) == -1)
            emergency_end(server);
    if (buffer)
        write(2, buffer, strlen(buffer));
    if (server->debug)
        debug_logger(server, message, log);
    if (buffer)
        free(buffer);
    need_stop(server, is_end);
}
