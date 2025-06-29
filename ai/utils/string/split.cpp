/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** split
*/

/**
 * @file split.cpp
 * @brief Splits strings by delimiter.  
 * @author Jason KOENIG  
 * @version 1.0  
 * @date 29/06/2025
 *
 * @see ai::utils::string::split
 */

#include "../utils.hpp"
#include <sstream>

std::vector<std::string> ai::utils::string::split(const std::string &str, char delim)
{
    std::vector<std::string> words;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delim)) {
        words.push_back(item);
    }
    return words;
}
