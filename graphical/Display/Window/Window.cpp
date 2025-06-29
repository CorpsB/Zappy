/*
** EPITECH PROJECT, 2025
** Window
** File description:
** Window
*/

/**
 * @file Window.cpp
 * @brief Implementation of the Window class used to manage the main SFML window.
 *
 * This file defines the methods of the `Window` class, which wraps around `sf::RenderWindow`
 * and provides utility functions for initializing, clearing, displaying, and resizing
 * the game window in the Zappy graphical client.
 *
 * The window is initialized with a fixed framerate limit (`FRAMERATE`) and basic window style
 * (title bar + close button). It is designed to be controlled externally by the `Game` class
 * and used by the `Renderer` to render game objects.
 *
 * @see Window.hpp, Game, sf::RenderWindow
 * @author Thomas Camuset
 * @date 2025
 * @version 1.0
 */

#include "Window.hpp"

void Window::init(unsigned int width, unsigned int height)
{
    _window.create(sf::VideoMode({width, height}), "Zappy", sf::Style::Titlebar | sf::Style::Close);
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
