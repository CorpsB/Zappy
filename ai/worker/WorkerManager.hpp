/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** WorkerManager
*/

/**
 * @file WorkerManager.hpp
 * @brief Singleton managing AI worker threads.
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @details
 * Provides methods for spawning AI workers in separate threads,
 * retrieving the current worker count, and joining all threads
 * upon shutdown.
 *
 * @see ai::entity::AI
 * @see ai::parser::Config
 */

#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include "../entity/AI.hpp"
#include "../parser/parser.hpp"

namespace ai::worker {
    /**
     * @class WorkerManager
     * @brief Handles lifecycle of AI worker threads.
     * @details
     * Implements the singleton pattern to ensure a single global
     * manager that can spawn, count, and join worker threads safely.
     *
     * @see spawnWorker()
     * @see getWorkerCount()
     * @see joinAll()
     */
    class WorkerManager {
        public:
            /**
             * @brief Retrieves the singleton instance.
             * @return Reference to the single WorkerManager instance.
             */
            static WorkerManager &getInstance();

            /**
             * @brief Spawns a new AI worker thread.
             * @param config Configuration parameters for the AI bot.
             * @details
             * Locks internal mutex, assigns a unique ID to the worker,
             * and launches a thread that constructs and runs an AI bot.
             * Exceptions are caught and logged.
             */
            void spawnWorker(const ai::parser::Config &config);

            /**
             * @brief Gets the number of active worker threads.
             * @return The current count of worker threads.
             * @details
             * Locks internal mutex to safely access the thread vector size.
             */
            int getWorkerCount();

            /**
             * @brief Waits for all worker threads to finish.
             * @details
             * Repeatedly swaps out the thread list under lock and joins each
             * thread. Sleeps briefly between iterations to avoid busy-wait.
             */
            void joinAll();

        private:
            /**
             * @brief Default constructor.
             * @details Initializes the worker ID counter to zero.
             */
            WorkerManager();

            std::vector<std::thread> _threads; // container of worker threads
            std::mutex _mutex; // protects access to _threads and _id
            unsigned _id; // unique id generator for workers
    };
}
