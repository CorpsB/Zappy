/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** help
*/

/**
 * @file help.cpp
 * @brief Print help command.
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 * 
 * @see parser.hpp
 */

#include <iostream>

/**
 * @brief Prints usage instructions for the Zappy client.
 */
void print_help_message()
{
    std::cout << "Usage: ./zappy_ai -p PORT -n NAME [options]" << std::endl << std::endl
        << "    -p, --port <int>       Port number" << std::endl
        << "    -n, --name <string>    Name of the team" << std::endl << std::endl
        << "    [options]" << std::endl
        << "    -h, --host <string>    Hostname (default: localhost)" << std::endl
        << "    -c, --count <int>      Number of bots (default: 1)" << std::endl
        << "    -d, --debug            Enable debug mode" << std::endl
        << "    --help                 Show this help message" << std::endl;
}
