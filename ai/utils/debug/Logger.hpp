/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Logger
*/

#pragma once

#include <string>
#include <vector>

namespace ai::utils::debug
{
    class Logger {
        public:
            Logger();
            ~Logger() = default;

            void setup(bool debug, const std::string &thread_name);
            void log(const std::string &msg);
            void display();

        private:
            bool _debug;
            std::string _thread_name;
            std::vector<std::string> _logs;
    };
}
