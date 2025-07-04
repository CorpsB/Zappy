/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** main
*/

/**
 * @file main.c
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06-29
 * @brief Entry point of the Zappy server.
 *
 * This file contains the main function of the Zappy server.
 * It is responsible for:
 * - Parsing command-line arguments
 * - Enabling debug mode if requested
 * - Initializing the server structure
 * - Generating the map and setting up the teams
 * - Handling the SIGINT signal for graceful shutdown
 * - Launching the main loop of the server
 *
 * The program can be launched with the `-h` option to display the help.
 * This help details all required options like map size, teams, port,
 * frequency, and number of clients per team.
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

bool sigint;

/**
 * @brief Print help message to stdout.
 * @return Always returns 0.
*/
int print_help(void)
{
    write(1, "USAGE:\n", 7);
    write(1, "./zappy_server -p port -x width -y height -n name1 name2\n", 57);
    write(1, "\n", 1);
    write(1, "DESCRIPTION:\n", 13);
    write(1, "  -p port        Port number for the server to listen on", 55);
    write(1, ".\n", 2);
    write(1, "  -x width       Width of the world (min 10).\n", 45);
    write(1, "  -y height      Height of the world (min 10).\n", 46);
    write(1, "  -n nameX [...] Names of the teams (at least 1).\n", 50);
    write(1, "  -c clientsNb   Number of authorized clients per team.\n", 55);
    write(1, "  -f freq        Server frequency in ticks per second ", 53);
    write(1, "(2 <= f <= 10000).\n", 19);
    write(1, "  -d             Enable debug mod.\n", 35);
    write(1, "\n", 1);
    write(1, "Example:\n", 9);
    write(1, "  ./zappy_server -p 4242 -x 20 -y 20", 36);
    write(1, "-n Team1 Team2 -c 5 -f 100\n", 27);
    return 0;
}

/**
 * @brief Detect and parse a specific command-line argument.
 * @param i Current index in the argument array.
 * @param av Array of arguments.
 * @param server Pointer to the server structure.
 * @return New index after parsing, or -1 on error.
*/
int parser_detector(int i, char **av, server_t *server)
{
    if (av[i] && strncmp(av[i], "-p", 2) == 0 && av[i + 1])
        return parse_port(av[i + 1], server, i);
    if (av[i] && strncmp(av[i], "-x", 2) == 0 && av[i + 1])
        return parse_width(av[i + 1], server, i);
    if (av[i] && strncmp(av[i], "-y", 2) == 0 && av[i + 1])
        return parse_height(av[i + 1], server, i);
    if (av[i] && strncmp(av[i], "-n", 2) == 0 && av[i + 1])
        return parse_teams(av, server, i);
    if (av[i] && strncmp(av[i], "-c", 2) == 0 && av[i + 1])
        return parse_client(av[i + 1], server, i);
    if (av[i] && strncmp(av[i], "-f", 2) == 0 && av[i + 1])
        return parse_frequency(av[i + 1], server, i);
    if (av[i] && strncmp(av[i], "-d", 2) == 0)
        i++;
    return i;
}

/**
 * @brief Parse all command-line arguments and detect errors.
 * @param ac Argument count.
 * @param av Argument array.
 * @param server Pointer to the server structure.
 * @return true if parsing is successful, false otherwise.
*/
bool parse_and_find_error(int ac, char **av, server_t *server)
{
    for (int i = 0; i < ac; i++) {
        i = parser_detector(i, av, server);
        if (i < 0) {
            logger(server, "Parser error found. Please try -h.", ERROR, false);
            return false;
        }
    }
    if (server->frequency == 0 ||
        server->height == 0 ||
        server->width == 0 ||
        server->starter_eggs_number == 0 ||
        server->port == 0 ||
        server->teams == NULL)
            return false;
    return true;
}

/**
 * @brief Check if debug mode is requested via arguments and enable it.
 * If the "-d" flag is present, debug mode is enabled and debug logs
 * will be written to "debug.log".
 * @param server Pointer to the server structure.
 * @param av Array of arguments.
*/
static void need_debug(server_t *server, char **av)
{
    for (int i = 0; av[i] != NULL; i++) {
        if (strncmp(av[i], "-d", 2) == 0) {
            server->debug = true;
            server->debug_fd = open("debug.log",
                O_WRONLY | O_CREAT | O_TRUNC, 0644);
            return;
        }
    }
}

void sigint_handler(int sig)
{
    (void)sig;
    sigint = true;
    if (printf("[WARNING] - SIGINT SIGNAL SEND.") == -1)
        exit(84);
}

/**
 * @brief Main entry point of the server.
 * @param ac Argument count.
 * @param av Argument array.
 * @return 0 on successful execution, or help message if arguments
 * are invalid.
*/
int main(int ac, char **av)
{
    server_t *server = add_server();

    sigint = false;
    if (ac == 1 || (ac == 2 && strncmp(av[1], "-h", 2) == 0))
        return print_help();
    need_debug(server, av);
    if (!parse_and_find_error(ac, av, server))
        return print_help();
    complete_team_data(server);
    srand(time(NULL));
    map_generator(server);
    debug_print_resource_map(server);
    signal(SIGINT, sigint_handler);
    run_server(server);
    free_server(server);
    return 0;
}
