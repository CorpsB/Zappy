/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Update
*/

#include "InputHandler.hpp"

namespace Renderer
{
    void InputHandler::switchInput(bool &keyToggle, bool &keyWasPressed, sf::Keyboard::Key key)
    {
        if (sf::Keyboard::isKeyPressed(key)) {
            if (!keyWasPressed) {
                keyToggle = !keyToggle;
                keyWasPressed = true;
            }
        } else {
            keyWasPressed = false;
        }
    }
} // namespace Renderer
