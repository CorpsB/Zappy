/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Error
*/

/**
 * @file Error.hpp
 * @brief Defines the Error exception class for AI utilities.
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @details
 * Provides a custom exception type that carries both an origin
 * (where in the code it was thrown) and a descriptive message.
 */

#pragma once

#include <exception>
#include <string>

namespace ai::utils::exception
{
    /**
     * @class Error
     * @brief Custom exception with location and message.
     *
     * @details
     * Extends std::exception to include the component or function
     * name (`where`) where the error occurred along with the error
     * message (`what`).
     */
    class Error : public std::exception {
        public:
            /**
             * @brief Constructs an Error with location and message.
             * @param where The origin (file/module/function) of the error.
             * @param what  The descriptive error message.
             */
            Error(const std::string &where, const std::string &what);

            /**
             * @brief Retrieves the descriptive error message.
             * @return The error message as a C-string.
             */
            const char *what() const noexcept override;

            /**
             * @brief Retrieves the origin of the error.
             * @return The origin (where) as a C-string.
             */
            const char *where() const noexcept;

        private:
            const std::string _where; // origin of the exception
            const std::string _what; // descriptive error message
    };
}
