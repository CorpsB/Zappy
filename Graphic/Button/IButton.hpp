/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Button
*/

#pragma once

#include <iostream>

#include "../Sprite/Sprite.hpp"

class IButton {
    public:
        virtual ~IButton() = default;

        virtual void setPosition(float x, float y) = 0;

        virtual void draw(sf::RenderWindow &window) = 0;

        virtual void action() = 0;
};
