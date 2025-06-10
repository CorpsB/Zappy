/*
** EPITECH PROJECT, 2025
** Event
** File description:
** Event
*/

#include "Event.hpp"

Event::Event()
{
}

Event::~Event()
{
}

int Event::getEvent(sf::RenderWindow &window)
{
    while (window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            return -1;
    }
    return 0;
}
