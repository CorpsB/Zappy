/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** capitalize
*/

/**
 * @file capitalize.cpp
 * @brief Capitalizes first letter of a string.  
 * @author Jason KOENIG  
 * @version 1.0  
 * @date 29/06/2025
 *
 * @see ai::utils::string::capitalize
 */

#include "../utils.hpp"

std::string ai::utils::string::capitalize(const std::string &str)
{
    if (str.empty())
        return str;

    std::string result = str;
    if (std::islower(static_cast<unsigned char>(result[0])))
        result[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[0])));
    return result;
}
