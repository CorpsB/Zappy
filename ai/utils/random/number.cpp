/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** number
*/

/**
 * @file number.cpp
 * @brief Random number generation implementation.  
 * @author Jason KOENIG  
 * @version 1.0  
 * @date 29/06/2025
 *
 * @see ai::utils::random::number
 */

#include <random>
#include "../utils.hpp"

unsigned int ai::utils::random::number(unsigned int minimum, unsigned int maximum)
{
    std::random_device rd; // random device for seeding
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dist(minimum, maximum);

    return dist(gen);
}
