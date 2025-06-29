/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** main
*/

/**
 * @file main.cpp
 * @brief Entry point for the Zappy AI client application.  
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @details
 * Parses command‑line arguments, configures debug mode,
 * spawns AI worker threads, and waits for their completion.
 */

#include "parser/parser.hpp"
#include "worker/WorkerManager.hpp"
#include <vector>
#include <thread>

/**
 * @brief Program entry point.
 * @param ac Argument count.
 * @param av Argument vector.
 * @return Exit status code (0 on success, 84 on parse error).
 *
 * @details
 * Initializes the Config struct, invokes the parser, prints debug
 * mode status, spawns the configured number of AI workers, and
 * waits for all to finish.
 */
int main(int ac, char **av)
{
    ai::parser::Config config;

    if (!ai::parser::parse(ac, av, config) && !config.help)
        return 84;

    if (config.debug)
        std::cout << "[Main] Debug mode ENABLED." << std::endl;
    else
        std::cout << "[Main] Debug mode DISABLED. Logs will print on exit or error." << std::endl;

    ai::worker::WorkerManager &manager = ai::worker::WorkerManager::getInstance();
    for (int i = 0; i < config.count; ++i)
        manager.spawnWorker(config);
    manager.joinAll();
    return 0;
}
