/*
** EPITECH PROJECT, 2025
** Window
** File description:
** Window
*/

#include "Window.hpp"

void Window::init()
{
    _window.create(sf::VideoMode({1920, 1080}), "Zappy");
    _window.setFramerateLimit(FRAMERATE);
}

void Window::stop()
{
    _window.close();
}

void Window::clear()
{
    _window.clear();
}

void Window::display()
{
    _window.display();
}

sf::RenderWindow &Window::getWindow()
{
    return _window;
}

void Window::setWindowSize(unsigned int width, unsigned int height)
{
    sf::Vector2u newSize = {width, height};

    _window.setSize(newSize);
}
