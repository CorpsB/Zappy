/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** AI
*/

#include "AI.hpp"
#include "../network/Socket.hpp"

ai::entity::AI::AI(int id)
{
    _id = id;
    _level = 1;
    _food_level = 1;
    _goal = FOOD;
    _thread_name = std::string("[Bot ") + std::to_string(id) + std::string("]");
}

void ai::entity::AI::start(const ai::parser::Config &config)
{
    _logger.setup(config.debug, _thread_name);
    _socket.setup(_thread_name, config.name);
    _socket.initSocket(config.port, config.host);
    _socket.connectServer();
    _socket.greetsServer();
}

void ai::entity::AI::stop()
{
    _logger.display();
}

void ai::entity::AI::run(const ai::parser::Config &config)
{
    start(config);
    stop();
}
