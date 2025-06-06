/*
** EPITECH PROJECT, 2025
** Window
** File description:
** Window
*/

#include "Window.hpp"

Window::Window()
{
}

Window::~Window()
{
}

void Window::init()
{
    this->_window.create(sf::VideoMode({1920, 1080}), "Zappy");
    // this->_window.setFramerateLimit(FRAMERATE);
}

void Window::stop()
{
    this->_window.close();
}

void Window::clear()
{
    this->_window.clear();
}

void Window::display()
{
    this->_window.display();
}

sf::RenderWindow &Window::getWindow()
{
    return this->_window;
}

void Window::setSizeWindow(unsigned int x, unsigned int y)
{
    sf::Vector2u newSize = {x, y};

    this->_window.setSize(newSize);
}
