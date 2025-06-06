/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** AButton
*/

#ifndef ABUTTON_HPP
    #define ABUTTON_HPP

#include "IButton.hpp"

class AButton : public IButton {
    public:
        AButton(const sf::Color &color, int width, int height);
        AButton(const std::string &textureFileName, int width, int height);

        void setPosition(float x, float y) override;

        void draw(sf::RenderWindow &window) override;

        virtual void action() = 0;
    protected:
        Sprite _sprite;
        sf::RectangleShape _rect;
        
        bool _hasTexture;
};

#endif
