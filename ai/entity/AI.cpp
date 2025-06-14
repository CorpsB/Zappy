/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** AI
*/

#include "AI.hpp"

ai::entity::AI::AI(parser::Config &config, int id)
{
    _config = std::make_shared<ai::parser::Config>(config);
    _id = id;
    _level = 1;
    _food_level = 0;
    _goal = FOOD;
}
