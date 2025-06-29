/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** int
*/

/**
 * @file integer.cpp
 * @brief Integer validation implementation.  
 * @author Jason KOENIG  
 * @version 1.0  
 * @date 29/06/2025
 *
 * @see ai::utils::validation::integer
 */

#include "../utils.hpp"

bool ai::utils::validation::integer(int val, const std::string &str_val)
{
    if (str_val.size() == std::to_string(val).size())
        return true;
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
    logger.log("[Error] Invalid int " + str_val);
    return false;
}
