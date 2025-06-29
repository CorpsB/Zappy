/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Persona
*/

/**
 * @file Persona.hpp
 * @brief Generates and exposes personality trait values for AI entities.  
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @details
 * Randomly produces MBTI-based persona traits—Introversion, LostInThought,
 * Empatic, and Spontaneous—using helper random utilities.
 */

#pragma once

#include <string>

namespace ai::entity
{
    /**
     * @class Persona
     * @brief Encapsulates randomly generated personality traits.
     */
    class Persona {
        public:
            /**
             * @brief Constructs a Persona and generates trait values.
             */
            Persona();

            /**
             * @brief Virtual destructor.
             */
            ~Persona() = default;

            /**
             * @brief Retrieves the Introversion trait (0–100).
             * @return Introversion score.
             */
            unsigned int getIntroversion();

            /**
             * @brief Retrieves the LostInThought trait (0–100).
             * @return LostInThought score.
             */
            unsigned int getLostInThought();

            /**
             * @brief Retrieves the Empatic trait (0–100).
             * @return Empatic score.
             */
            unsigned int getEmpatic();

            /**
             * @brief Retrieves the Spontaneous trait (0–100).
             * @return Spontaneous score.
             */
            unsigned int getSpontaneous();

        private:
            /**
             * @brief Populates trait values based on a random MBTI code.
             */
            void generatePersona();

            /**
             * @brief Randomly selects an MBTI type code.
             * @return A four‑letter MBTI string.
             */
            std::string getMBTI();

            unsigned int _introversion;     // introversion score
            unsigned int _lost_in_thought;  // lostInThought score
            unsigned int _empatic;          // empatic score
            unsigned int _spontaneous;      // spontaneous score
    };
}
