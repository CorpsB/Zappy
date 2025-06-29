/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Game
*/

#pragma once

#include <iostream>
#include <memory>

#include "../Window/Window.hpp"
#include "../Event/Event.hpp"
#include "../../3DRenderer/include/Renderer.hpp"

#include "Interpreter/Interpreter.hpp"

class Game {
    public:
        Game(std::shared_ptr<Renderer::Renderer> renderer) : _interpreter(renderer), _renderer(renderer) {};
        ~Game() = default;

        /**
         * @brief Returns a singleton instance of the Game class.
         *
         * If the instance does not exist, it is created with the given renderer.
         *
         * @param renderer Shared pointer to the Renderer instance.
         * @return Reference to the unique Game instance.
         */
        static Game &GetInstance(std::shared_ptr<Renderer::Renderer> renderer);

        /**
         * @brief Initializes the game window and the 3D renderer.
         *
         * Creates a window with default resolution and initializes the renderer
         * using the created SFML window context.
         *
         * @param renderer Shared pointer to the renderer instance to use.
         */
        void init(std::shared_ptr<Renderer::Renderer> renderer);
        /**
         * @brief Starts the main game loop.
         *
         * Polls events, updates the renderer state, and draws the current frame.
         * The loop runs until a close event is detected.
         */
        void run();
        /**
         * @brief Stops and closes the game window.
         */
        void stop();

        /**
         * @brief Sends raw server data to the interpreter for processing.
         *
         * Delegates command parsing and in-game action triggering to the Interpreter.
         *
         * @param data Server message or instruction string.
         */
        void processData(const std::string &data);

        /**
         * @brief Returns the shared Renderer instance used by the game.
         *
         * @return Shared pointer to the Renderer.
         */
        std::shared_ptr<Renderer::Renderer> getRenderer() const;

    private:
        Window _window;
        Event _event;
        sf::Clock _clock;

        Interpreter _interpreter;
        std::shared_ptr<Renderer::Renderer> _renderer;
};
