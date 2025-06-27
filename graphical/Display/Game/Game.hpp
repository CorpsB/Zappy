/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Game
*/

#pragma once

#include <iostream>

#include "../Window/Window.hpp"
#include "../Event/Event.hpp"
#include "../../3DRenderer/include/Renderer.hpp"

#include "Interpreter/Interpreter.hpp"

class Game {
    public:
        Game() {}
        ~Game() = default;

        static Game &GetInstance();

        /**
         * @brief Initialize the game window
         */
        void init();
        /**
         * @brief Starts the game loop
         */
        void run();
        /**
         * @brief Stop the game
         */
        void stop();

        /**
         * @brief Analyzes 'data' and modifies the graphic elements
         * @param data Command send by the server
         */
        void processData(const std::string &data);
    private:
        Window _window;
        Event _event;
        sf::Clock _clock;

        Interpreter _interpreter;
};
