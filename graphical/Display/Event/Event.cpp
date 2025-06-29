/*
** EPITECH PROJECT, 2025
** Event
** File description:
** Event
*/

/**
 * @file Event.cpp
 * @brief Implémentation de la classe Event (gestion des événements SFML).
 *
 * Ce fichier implémente la méthode `getEvent()` qui récupère les événements
 * d'une fenêtre SFML passée en paramètre. Actuellement, seule la fermeture de
 * la fenêtre (`sf::Event::Closed`) est interceptée, ce qui retourne `-1` pour
 * signaler la demande de fermeture au moteur principal.
 *
 * @return `-1` si l'utilisateur ferme la fenêtre, `0` sinon.
 * @see Event.hpp, sf::RenderWindow
 * @date 2025
 * @version 1.0
 * @note Ce système peut être étendu à d'autres événements (touches, clics, etc.).
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
