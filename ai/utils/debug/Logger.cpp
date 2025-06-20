/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Logger
*/

#include "Logger.hpp"
#include <iostream>

ai::utils::debug::Logger &ai::utils::debug::Logger::GetInstance()
{
    static Logger _logger;
    return _logger;
}

ai::utils::debug::Logger::Logger()
{
    _thread_name = "";
    _debug = false;   
}

void ai::utils::debug::Logger::setup(bool debug, const std::string &thread_name)
{
    _thread_name = thread_name;
    _debug = debug;

    if (_debug)
        std::cout << "[Main] Debug mode ENABLED." << std::endl;
    else
        std::cout << "[Main] Debug mode DISABLED. Logs will print on exit or error." << std::endl;
}

void ai::utils::debug::Logger::log(const std::string &msg)
{
    if (_debug)
        _logs.push_back(msg);
    else
        std::cout << _thread_name << " " << msg << std::endl;
}

void ai::utils::debug::Logger::display()
{
    for (const auto log : _logs)
        std::cout << _thread_name << " " << log << std::endl;
    _logs.clear();
}
