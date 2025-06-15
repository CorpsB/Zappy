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

class Game {
    public:
        Game() {}
        ~Game() = default;

        static Game &GetInstance();

        void init();
        void run();
        void stop();
    private:
        Window _window;
        Event _event;

        sf::Clock _clock;

        std::vector<int> _entitiesId;
};
