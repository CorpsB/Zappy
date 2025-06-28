/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Error
*/

#pragma once

#include <exception>
#include <string>

namespace ai::utils::exception
{
    class Error : public std::exception {
        public:
            Error(const std::string &where, const std::string &what);

            const char *what() const noexcept override;
            const char *where() const noexcept;

        private:
            const std::string _where;
            const std::string _what;
    };
}
