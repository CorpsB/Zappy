/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** AI
*/

#pragma once

#include <string>
#include <memory>
#include "persona/Persona.hpp"
#include "../parser/parser.hpp"

namespace ai::entity
{
    enum Goal {
        FOOD,
        STONE,
        MEETUP,
        ELEVATION
    };

    class AI {
        public:
            AI(int id);
            ~AI() = default;

            void run(const ai::parser::Config &config);

        private:
            std::string _name;
            unsigned _id;
            unsigned _level;
            unsigned _food_level;
            Goal _goal;
            Persona _persona;
    };
}
