/*
** EPITECH PROJECT, 2025
** Window
** File description:
** Window
*/

#pragma once

#define FRAMERATE 60

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Window {
    public:
        Window() {};
        ~Window() {};

        sf::RenderWindow &getWindow();
        void setWindowSize(unsigned int x, unsigned int y);

        void init();
        void stop();
        void clear();
        void display();
    private:
        sf::RenderWindow _window;
};
