/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Inventory
*/

#pragma once

#include <map>
#include <string>

namespace ai::entity
{
    class Inventory {
        public:
            Inventory();
            ~Inventory() = default;

            void update(const std::string &storage);

            void setItem(const std::string &item, int quantity);
            int getItem(const std::string &item);

        private:
            std::map<std::string, int> _storage;
    };
}
