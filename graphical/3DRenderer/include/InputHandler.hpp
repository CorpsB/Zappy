/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** InputHandler
*/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Camera.hpp"
#include "Renderer.hpp"


namespace Renderer {
    class InputHandler {
        public:
            InputHandler() = default;
            ~InputHandler() = default;
            void switchInput(bool &keyToggle, bool &keyWasPressed, sf::Keyboard::Key key);
        private:
    };
}
