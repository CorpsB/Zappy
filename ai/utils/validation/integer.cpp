/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** int
*/

#include "../utils.hpp"

bool ai::utils::validation::integer(int val, const std::string &str_val)
{
    if (str_val.size() == std::to_string(val).size())
        return true;
    std::cerr << "Error: Invalid int " << str_val << std::endl;
    return false;
}
