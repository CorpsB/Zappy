/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_sst_t.c
*/

/**
 * @file cmd_sst.c
 * @brief Implements the "sst" graphical command for the Zappy server.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * Handles the "sst" command which sets the game frequency (ticks per second).
 * Parses and validates the frequency argument, then updates the server's
 * frequency setting accordingly.
 * If the argument is invalid, the server replies "ko\n".
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include <ctype.h>

/**
 * @brief Parses the frequency argument from the GUI command "sst".
 * This function extracts and validates a numeric argument from the args array,
 * representing the desired game frequency (ticks per second).
 * @param args The command arguments (should contain at least two elements).
 * @param freq_out Pointer to store the parsed frequency if valid.
 * @return true if parsing and validation succeed, false otherwise.
*/
static bool parse_sst_argument(char **args, long *freq_out)
{
    char *end;
    long freq;

    if (!args || !args[1])
        return false;
    freq = strtol(args[1], &end, 10);
    while (*end && isspace((unsigned char)*end))
        end++;
    if (*end || freq <= 0)
        return false;
    *freq_out = freq;
    return true;
}

void cmd_sst(server_t *server, int index, char **args)
{
    int fd;
    long freq;

    fd = server->poll.pollfds[index].fd;
    if (!parse_sst_argument(args, &freq)) {
        send_str(server, fd, "ko\n", false);
        return;
    }
    server->frequency = (unsigned int)freq;
    event_sgt(server);
}
