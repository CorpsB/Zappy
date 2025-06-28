/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Sprite
*/

#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Sprite {
    public:
        Sprite(const std::string &textureFileName);

        sf::Sprite &getSprite();
        sf::Texture &getTexture();

        void setTexture(const std::string &textureFileName);

        void draw(sf::RenderWindow &window);
        
        void setPosition(int x, int y);

    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
};
