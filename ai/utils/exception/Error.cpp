/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Error
*/

/**
 * @file Error.cpp
 * @brief Implements the Error exception class methods.
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @see Error.hpp
 */

#include "Error.hpp"

ai::utils::exception::Error::Error(const std::string &where, const std::string &what) :
    _where(where), _what(what)
{
}

const char *ai::utils::exception::Error::where(void) const noexcept
{
    return _where.c_str();
}

const char *ai::utils::exception::Error::what(void) const noexcept
{
    return _what.c_str();
}
