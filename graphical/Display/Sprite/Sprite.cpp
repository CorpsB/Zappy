/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Sprite
*/

#include "Sprite.hpp"

Sprite::Sprite(const std::string &textureFileName)
{
    if (!_texture.loadFromFile(textureFileName))
        throw std::runtime_error("Failed to load file : " + textureFileName);
    _sprite.setTexture(_texture);
}

sf::Sprite &Sprite::getSprite()
{
    return _sprite;
}

sf::Texture &Sprite::getTexture()
{
    return _texture;
}

void Sprite::setTexture(const std::string &textureFileName)
{
    if (!_texture.loadFromFile(textureFileName))
        throw std::runtime_error("Failed to load file : " + textureFileName);
    _sprite.setTexture(_texture);
}

void Sprite::setPosition(int x, int y)
{
    _sprite.setPosition(x, y);
}

void Sprite::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
}
