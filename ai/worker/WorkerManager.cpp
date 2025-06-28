/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** WorkerManager
*/

#include "WorkerManager.hpp"

ai::worker::WorkerManager::WorkerManager() : _id(0)
{
}

ai::worker::WorkerManager &ai::worker::WorkerManager::getInstance()
{
    static WorkerManager instance;
    return instance;
}

void ai::worker::WorkerManager::spawnWorker(const ai::parser::Config &config)
{
    std::lock_guard<std::mutex> lock(_mutex);
    const int id = _id++;

    _threads.emplace_back([=]() {
        ai::utils::debug::Logger &logger = ai::utils::debug::Logger::GetInstance();

        try {
            ai::entity::AI bot(id);
            bot.run(config);
        } catch (const ai::utils::exception::Error &e) {
            logger.log("[Exception] " + std::string(e.what()));
        } catch (const std::exception &e) {
            logger.log("[Unhandled Exception] " + std::string(e.what()));
        } catch (...) {
            logger.log("[Unknown Exception] Something went bad.");
        }
        logger.display();
    });
}

int ai::worker::WorkerManager::getWorkerCount()
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _threads.size();
}

void ai::worker::WorkerManager::joinAll()
{
    while (true) {
        std::vector<std::thread> localThreads;

        {
            std::lock_guard<std::mutex> lock(_mutex);
            if (_threads.empty())
                break;
            localThreads.swap(_threads);
        }

        for (auto &t : localThreads)
            if (t.joinable())
                t.join();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
