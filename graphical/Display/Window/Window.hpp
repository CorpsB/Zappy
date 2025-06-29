/*
** EPITECH PROJECT, 2025
** Window
** File description:
** Window
*/

/**
 * @file Window.hpp
 * @brief Declaration of the Window class, a wrapper around SFML's RenderWindow.
 *
 * The Window class provides a lightweight interface to manage the main application window
 * using SFML. It handles window initialization, resizing, clearing, and display, and is used
 * by the `Game` class to handle frame rendering and input.
 *
 * The internal window is exposed via `getWindow()` to allow other components (like the renderer)
 * to draw directly on the SFML context.
 *
 * Constant:
 * - `FRAMERATE`: The fixed frame rate limit applied to the window (60 FPS).
 *
 * @author Thomas Camuset
 * @date 2025
 * @version 1.0
 * @see Game, sf::RenderWindow
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

        /**
         * @brief Initializes the SFML window with the given dimensions.
         *
         * Creates a window with the specified width and height,
         * sets the window title to "Zappy", and applies the default style
         * (title bar + close button). Also sets the framerate limit to `FRAMERATE`.
         *
         * @param width Width of the window in pixels.
         * @param height Height of the window in pixels.
         */
        void init(unsigned int width, unsigned int height);
        /**
         * @brief Closes the SFML window.
         *
         * Stops the rendering context and destroys the window.
         * This should be called when exiting the game loop.
         */
        void stop();
        /**
         * @brief Clears the window's contents.
         *
         * Prepares the window for the next frame by clearing everything
         * that was drawn during the previous frame.
         */
        void clear();
        /**
         * @brief Displays everything that has been drawn to the window.
         *
         * Swaps the window buffer and renders all visible elements.
         * Should be called at the end of each frame.
         */
        void display();
    private:
        sf::RenderWindow _window;
};