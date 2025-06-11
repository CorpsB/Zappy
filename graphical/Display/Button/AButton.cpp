/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** AButton
*/

#include "AButton.hpp"

AButton::AButton(const sf::Color &color, int width, int height) : _sprite("")
{
    _rect.setSize(sf::Vector2f(width, height));
    _rect.setFillColor(color);
    _hasTexture = false;
}

AButton::AButton(const std::string &textureFileName, int width, int height) : _sprite(textureFileName)
{
    sf::Vector2u textureSize = _sprite.getTexture().getSize();
    sf::Vector2f sizeToApply;

    sizeToApply.x = textureSize.x / width;
    sizeToApply.y = textureSize.y / height;
    _sprite.getSprite().setScale(sizeToApply);
    _hasTexture = true;
}

void AButton::setPosition(float x, float y)
{
    if (!_hasTexture) {
        _rect.setPosition(x, y);
        return;
    }
    _sprite.getSprite().setPosition(x, y);
}

void AButton::draw(sf::RenderWindow &window)
{
    if (!_hasTexture)
        window.draw(_rect);
    _sprite.draw(window);
}
