/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** parser
*/

/**
 * @file parser.hpp
 * @brief Command‑line argument parser for Zappy AI client.
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @details
 * Defines the Config struct holding parsed options and
 * the parse() function to populate it from argv.
 */

#pragma once

#include <string>

namespace ai::parser
{
    /**
     * @struct Config
     * @brief Holds command‑line options for the AI client.
     */
    struct Config {
        int         port  = -1;               // Port number (required)
        std::string name;                     // Team name (required)
        std::string host  = "127.0.0.1";      // Server host (default: 127.0.0.1)
        int         count = 1;                // Number of bots (default: 1)
        bool        debug = false;            // Enable debug mode
        bool        help  = false;            // Show help and exit
    };

    /**
     * @brief Parses command‑line arguments into a Config.
     * @param ac     Argument count.
     * @param av     Argument vector.
     * @param config Config object to populate.
     * @return true if parsing succeeded (or help requested), false on error.
     */
    bool parse(int ac, char **av, Config &config);
}

/**
 * @brief Prints usage and option descriptions to stdout.
 */
void print_help_message();
