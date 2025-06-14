/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** parser
*/

#pragma once

#include <string>

namespace ai::parser {
    struct Config {
        int port = -1;
        std::string name;
        std::string host = "127.0.0.1";
        int count = 1;
        bool debug = false;
        bool help = false;
    };

    bool parse(int ac, char **av, Config &config);
}

void print_help_message();
