/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Logger
*/

#include "Logger.hpp"
#include <iostream>
#include <thread>

std::mutex ai::utils::debug::WRITE_LOCK;

ai::utils::debug::Logger &ai::utils::debug::Logger::GetInstance()
{
    thread_local Logger _logger;
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
}

void ai::utils::debug::Logger::log(const std::string &msg)
{
    if (_debug) {
        std::lock_guard<std::mutex> lock(WRITE_LOCK);
        std::cout << _thread_name << " " << msg << std::endl;
    } else
        _logs.push_back(msg);
}

void ai::utils::debug::Logger::display()
{
    std::lock_guard<std::mutex> lock(WRITE_LOCK);   
    for (const auto log : _logs)
        std::cout << _thread_name << " " << log << std::endl;
    _logs.clear();
}
