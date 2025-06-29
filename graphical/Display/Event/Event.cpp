/*
** EPITECH PROJECT, 2025
** Event
** File description:
** Event
*/

/**
 * @file Event.cpp
 * @brief Implementation of the Event class (SFML event handling).
 *
 * This file implements the `getEvent()` method, which retrieves events
 * from an SFML window passed as a parameter. Currently, only the window
 * close event (`sf::Event::Closed`) is intercepted, which returns `-1`
 * to signal a shutdown request to the main engine.
 *
 * @see Event.hpp, sf::RenderWindow
 * @date 2025
 * @version 1.0
 * @note This system can be extended to handle other events (keyboard, mouse, etc.).
 */

#include "Event.hpp"

int Event::getEvent(sf::RenderWindow &window)
{
    while (window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            return -1;
    }
    return 0;
}
