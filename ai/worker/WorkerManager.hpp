/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** WorkerManager
*/

#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include "../entity/AI.hpp"
#include "../parser/parser.hpp"

namespace ai::worker {
    class WorkerManager {
        public:
            static WorkerManager &getInstance();
            void spawnWorker(const ai::parser::Config &config);
            int getWorkerCount();
            void joinAll();

        private:
            WorkerManager();

            std::vector<std::thread> _threads;
            std::mutex _mutex;
            unsigned _id;
    };
}
