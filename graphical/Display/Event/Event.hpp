/*
** EPITECH PROJECT, 2025
** Event
** File description:
** Event
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
        Event();
        ~Event();

        int getEvent(sf::RenderWindow &window);
    private:
        sf::Event _event;
};
