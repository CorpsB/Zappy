/*
** EPITECH PROJECT, 2025
** Window
** File description:
** Window
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

#define FRAMERATE 60

#include "../../include/Header.hpp"

class Window {
    public:
        Window();
        ~Window();

        void init();
        void stop();
        void clear();
        void display();
        sf::RenderWindow &getWindow();
        void setSizeWindow(unsigned int x, unsigned int y);
    private:
        sf::RenderWindow _window;
};

#endif
