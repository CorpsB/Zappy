/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** utils
*/

#pragma once

#include <string>
#include <iostream>

namespace ai::utils
{
    namespace validation {
        bool integer(int val, const std::string &str_val);
        bool ipv4(const std::string &ip);
    }

    namespace random {
        unsigned int number(unsigned int minimum, unsigned int maximum);
    }
}
