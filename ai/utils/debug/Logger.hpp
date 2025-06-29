/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Logger
*/

/**
 * @file Logger.hpp
 * @brief Defines the Logger class for thread-safe logging in AI utilities.
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @details
 * Provides a singleton logger that can buffer messages when debugging is disabled
 * and flush them upon request, ensuring thread-safe output using a global mutex.
 */

#pragma once

#include <string>
#include <vector>
#include <mutex>

namespace ai::utils::debug
{
    extern std::mutex WRITE_LOCK; // global mutex for serializing console output

    /**
     * @class Logger
     * @brief Thread-safe singleton logger with buffered output.
     *
     * @details
     * Logger instances buffer messages internally when debug mode is off,
     * and immediately print them (with thread name prefixes) when debug is on
     * or upon calling display().
     */
    class Logger {
        public:
            Logger(Logger &other) = delete;
            void operator=(const Logger &) = delete;

            /**
             * @brief Retrieves the thread-local Logger instance.
             * @return Reference to the Logger singleton for the current thread.
             */
            static Logger &GetInstance();

            /**
             * @brief Configures the logger.
             * @param debug       Whether to print messages immediately.
             * @param thread_name Name prefix for all logged messages.
             */
            void setup(bool debug, const std::string &thread_name);

            /**
             * @brief Logs a message.
             * @param msg The message to log.
             *
             * @details
             * If debug mode is enabled, the message is printed immediately
             * under WRITE_LOCK; otherwise, it is buffered in `_logs`.
             */
            void log(const std::string &msg);

            /**
             * @brief Flushes and displays all buffered messages.
             *
             * @details
             * Prints all messages stored in `_logs` under WRITE_LOCK
             * and then clears the buffer.
             */
            void display();

        private:
            /**
             * @brief Constructs a Logger with default settings.
             */
            Logger();

            ~Logger() = default;

            bool _debug; // immediate-print flag
            std::string _thread_name; // prefix for each log entry
            std::vector<std::string> _logs; // buffer for deferred messages
    };
}
