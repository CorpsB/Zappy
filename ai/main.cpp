/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** main
*/

#include "parser/parser.hpp"
#include "entity/AI.hpp"
#include <vector>
#include <thread>

int main(int ac, char **av)
{
    ai::parser::Config config;

    if (!ai::parser::parse(ac, av, config) && !config.help)
        return 84;

    const unsigned int nthreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    const auto worker = [&](unsigned threadId) {
        ai::entity::AI bot(threadId);

        bot.run(config);
    };

    threads.reserve(nthreads);
    for (size_t i = 0; i < nthreads; ++i)
        threads.emplace_back(worker, i);
    for (auto &t : threads)
        t.join();
    return 0;
}
