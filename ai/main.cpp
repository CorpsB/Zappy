/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** main
*/

#include "parser/parser.hpp"
#include "worker/WorkerManager.hpp"
#include <vector>
#include <thread>

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
