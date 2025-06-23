/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** number
*/

#include <random>
#include "../utils.hpp"

unsigned int ai::utils::random::number(unsigned int minimum, unsigned int maximum)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minimum, maximum);

    return dist(gen);
}
