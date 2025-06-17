/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_sst_t.c
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

/**
 * @brief Sends the updated frequency to all connected graphical clients.
 * Iterates over all connected clients and notifies those identified as GUI
 * with the updated server frequency using the "sst" command.
 * @param server The server structure containing clients and
 * the frequency value.
*/
static void notify_gui_frequency(server_t *server)
{
    int fd;

    for (int i = 0; i < server->poll.client_index; i++) {
        if (server->poll.client_list[i].whoAmI == GUI) {
            fd = server->poll.pollfds[i].fd;
            dprintf(fd, "sst %u\n", server->frequency);
        }
    }
}

void cmd_sst(server_t *server, int index, char **args)
{
    int fd;
    long freq;

    fd = server->poll.pollfds[index].fd;
    if (check_graphical(server, index) != 0)
        return;
    if (!parse_sst_argument(args, &freq)) {
        dprintf(fd, "ko\n");
        return;
    }
    server->frequency = (unsigned int)freq;
    notify_gui_frequency(server);
}
