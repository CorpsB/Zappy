/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Sprite
*/

#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Sprite {
    public:
        Sprite(const std::string &textureFileName);

        sf::Sprite &getSprite();
        sf::Texture &getTexture();

        void setTexture(const std::string &textureFileName);

        void draw(sf::RenderWindow &window);
    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
};
