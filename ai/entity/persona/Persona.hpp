/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Persona
*/

#pragma once

#include <string>

namespace ai::entity
{
    class Persona {
        public:
            Persona();
            ~Persona() = default;

            unsigned int getIntroversion();
            unsigned int getLostInThought();
            unsigned int getEmpatic();
            unsigned int getSpontaneous();

        private:
            void generatePersona();
            std::string getMBTI();

            unsigned int _introversion;
            unsigned int _lost_in_thought;
            unsigned int _empatic;
            unsigned int _spontaneous;
    };
}
