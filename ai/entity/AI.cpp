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
    _name = std::string("[Bot ") + std::to_string(id) + std::string("]");
}

void ai::entity::AI::run(const ai::parser::Config &config)
{
    network::Socket socket(_name, config.name);

    socket.initSocket(config.port, config.host);
    socket.connectServer();
    socket.greetsServer();
}
