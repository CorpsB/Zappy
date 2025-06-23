/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** parser
*/

#include "parser.hpp"
#include "../utils/utils.hpp"
#include <iostream>

static bool parse_port(ai::parser::Config &config, const std::string &arg, int ac,
    char **av, int &i)
{
    if (ac < i + 1) {
        std::cerr << "Error: Missing value for " << arg << std::endl;
        return false;
    }
    ++i;
    config.port = std::atoi(av[i]);
    if (config.port < 0 || config.port > 65535) {
        std::cerr << "Error: Port must be in 0-65535 range." << std::endl;
        return false;
    }
    if (!ai::utils::validation::integer(config.port, std::string(av[i])))
        return false;
    return true;
}

static bool parse_name(ai::parser::Config &config, const std::string &arg, int ac,
    char **av, int &i)
{
    if (ac < i + 1) {
        std::cerr << "Error: Missing value for " << arg << std::endl;
        return false;
    }
    ++i;
    config.name = av[i];
    if (config.name == "GRAPHIC") {
        std::cerr << "Error: GRAPHIC team name is reserved. " << arg << std::endl;
        return false;
    }
    return true;
}

static bool parse_host(ai::parser::Config &config, const std::string &arg, int ac,
    char **av, int &i)
{
    if (ac < i + 1) {
        std::cerr << "Error: Missing value for " << arg << std::endl;
        return false;
    }
    ++i;
    config.host = av[i];
    if (!ai::utils::validation::ipv4(config.host))
        return false;
    return true;
}

static bool parse_count(ai::parser::Config &config, const std::string &arg, int ac,
    char **av, int &i)
{
    if (ac < i + 1) {
        std::cerr << "Error: Missing value for " << arg << std::endl;
        return false;
    }
    ++i;
    config.count = std::atoi(av[i]);
    if (config.count < 1) {
        std::cerr << "Error: Count cannot be negative or null." << std::endl;
        return false;
    }
    if (!ai::utils::validation::integer(config.count, std::string(av[i])))
        return false;
    return true;
}

bool ai::parser::parse(int ac, char **av, ai::parser::Config &config)
{
    for (int i = 1; i < ac; ++i) {
        std::string arg = av[i];

        if (arg == "-p" || arg == "--port") {
            if (!parse_port(config, arg, ac, av, i))
                return false;
        } else if (arg == "-n" || arg == "--name") {
            if (!parse_name(config, arg, ac, av, i))
                return false;
        } else if (arg == "-h" || arg == "--host") {
            if (!parse_host(config, arg, ac, av, i))
                return false;
        } else if (arg == "-c" || arg == "--count") {
            if (!parse_count(config, arg, ac, av, i))
                return false;
        } else if (arg == "-d" || arg == "--debug")
            config.debug = true;
        else if (arg == "--help") {
            print_help_message();
            config.help = true;
            return true;
        }
        else {
            std::cerr << "Error: Unknown option " << arg << std::endl << std::endl;
            print_help_message();
            return false;
        }
    }
    if (config.port == -1 || config.name.empty()) {
        std::cerr << "Error: --port and --name are required." << std::endl << std::endl;
        print_help_message();
        return false;
    }
    return true;
}
