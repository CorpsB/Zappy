/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Logger
*/

#pragma once

#include <string>
#include <vector>
#include <mutex>

namespace ai::utils::debug
{
    extern std::mutex WRITE_LOCK;

    class Logger {
        public:
            Logger(Logger &other) = delete;
            void operator=(const Logger &) = delete;

            static Logger &GetInstance();

            void setup(bool debug, const std::string &thread_name);
            void log(const std::string &msg);
            void display();

        private:
            Logger();
            ~Logger() = default;

            bool _debug;
            std::string _thread_name;
            std::vector<std::string> _logs;
    };
}
