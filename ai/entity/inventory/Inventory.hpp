/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Inventory
*/

/**
 * @file Inventory.hpp
 * @brief Manages resource counts for AI entities.  
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @details
 * Provides methods to parse inventory strings from the server,
 * store quantities, and retrieve or display them.
 */

#pragma once

#include <map>
#include <string>

namespace ai::entity
{
    /**
     * @class Inventory
     * @brief Tracks and updates quantities of in-game resources.
     */
    class Inventory {
        public:
            /**
             * @brief Constructs an Inventory with zeroed resources.
             */
            Inventory();

            /**
             * @brief Parses a server inventory string "[item1qty,item2qty,...]".
             * @param storage Raw inventory string from server.
             * @return true if parsing succeeded, false on format error.
             */
            bool update(const std::string &storage);

            /**
             * @brief Formats all resource counts into a printable string.
             * @return Human‑readable listing of resource quantities.
             */
            std::string print();

            /**
             * @brief Sets the quantity for a named resource.
             * @param item     Resource name (e.g., "food").
             * @param quantity Quantity to assign.
             */
            void setItem(const std::string &item, int quantity);

            /**
             * @brief Retrieves the stored quantity for a resource.
             * @param item Resource name.
             * @return Quantity, or -1 if the resource is unknown.
             */
            int getItem(const std::string &item);

        private:
            std::map<std::string, int> _storage; // map of resource→quantity
    };
}
