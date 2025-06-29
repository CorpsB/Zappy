/*
** EPITECH PROJECT, 2025
** Event
** File description:
** Event
*/

/**
 * @file Event.hpp
 * @brief Declaration of the Event class for SFML event handling in the Zappy client.
 *
 * The Event class is responsible for processing window-level events
 * in the Zappy graphical client using the SFML library. It currently
 * handles window close detection but is designed to be extended to support
 * other types of events such as keyboard inputs, mouse clicks, and
 * potentially server-triggered UI updates.
 *
 * In the future, an enumeration of all possible server instructions
 * may be added to manage interactions and graphical updates more effectively.
 *
 * @note This class may evolve into a central event dispatcher for user and server input.
 * @see sf::RenderWindow, sf::Event
 * @author Thomas Camuset
 * @date 2025
 * @version 1.0
 */

#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//-Cette classe sera utilisée pour gérer les différentes instructions du serveur
//-Il y aura probablement besoin de faire un enum avec toutes les instructions possibles
// pour pouvoir afficher des trucs sur la window
class Event {
    public:
        Event() {};
        ~Event() {};

        /**
         * @brief Retrieves events from the SFML window.
         *
         * This method checks the SFML events of the given window.
         * If the `sf::Event::Closed` event is detected, it returns `-1` to indicate
         * that the window should be closed.
         *
         * @param window Reference to the SFML window to analyze.
         * @return `-1` if a close event is detected, `0` otherwise.
         */
        int getEvent(sf::RenderWindow &window);
    private:
        sf::Event _event;
};
