/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** utils
*/

/**
 * @file utils.hpp
 * @brief Collection of utility functions for validation, randomness, and string manipulation.
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @details
 * Provides namespaces for validating inputs (integer, IPv4), generating random numbers,
 * and performing basic string operations (split, capitalize).
 */

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "exception/Error.hpp"
#include "debug/Logger.hpp"

namespace ai::utils
{
    namespace validation
    {
        /**
         * @brief Checks if the string representation corresponds to the integer value.
         * @param val The integer value parsed.
         * @param str_val The original string representation.
         * @return true if sizes match, false otherwise (and logs an error).
         */
        bool integer(int val, const std::string &str_val);

        /**
         * @brief Validates that a string is a correctly formatted IPv4 address.
         * @param ip The string to validate.
         * @return true if the string is a valid IPv4, false otherwise (and logs an error).
         */
        bool ipv4(const std::string &ip);
    }

    namespace random
    {
        /**
         * @brief Generates a random integer in the given inclusive range.
         * @param minimum The lower bound.
         * @param maximum The upper bound.
         * @return A pseudorandom number between minimum and maximum.
         */
        unsigned int number(unsigned int minimum, unsigned int maximum);
    }

    namespace string
    {
        /**
         * @brief Splits a string into tokens based on a delimiter character.
         * @param str The string to split.
         * @param delim The delimiter character.
         * @return A vector of substrings.
         */
        std::vector<std::string> split(const std::string &str, char delim);

        /**
         * @brief Capitalizes the first character of the string, if lowercase.
         * @param str The input string.
         * @return A new string with the first letter capitalized.
         */
        std::string capitalize(const std::string &str);
    }
}
