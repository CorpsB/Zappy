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

    if (config.debug)
        std::cout << "[Main] Debug mode ENABLED." << std::endl;
    else
        std::cout << "[Main] Debug mode DISABLED. Logs will print on exit or error." << std::endl;

    const unsigned int nthreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    const auto worker = [&](unsigned threadId) {
        ai::utils::debug::Logger &logger = ai::utils::debug::Logger::GetInstance();

        try {
            ai::entity::AI bot(threadId);
            bot.run(config);
        } catch (const ai::utils::exception::Error &e) {
            logger.log("[Exception] " + std::string(e.what()));
        } catch (const std::exception &e) {
            logger.log("[Unhandled Exception] " + std::string(e.what()));
        } catch (...) {
            logger.log("[Unknown Exception] Something went bad.");
        }
        logger.display();
    };

    threads.reserve(nthreads);
    for (size_t i = 0; i < nthreads; ++i)
        threads.emplace_back(worker, i);
    for (auto &t : threads)
        t.join();
    return 0;
}
