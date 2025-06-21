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

            bool update(const std::string &storage);
            std::string print();

            void setItem(const std::string &item, int quantity);
            int getItem(const std::string &item);

        private:
            std::map<std::string, int> _storage;
    };
}
