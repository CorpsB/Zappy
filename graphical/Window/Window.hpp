/*
** EPITECH PROJECT, 2025
** Window
** File description:
** Window
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

    #define FRAMERATE 60

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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
