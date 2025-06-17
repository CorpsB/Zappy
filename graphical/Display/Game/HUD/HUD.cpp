/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** HUD
*/

#include "HUD.hpp"

void HUD::setMapSize(std::size_t x, std::size_t z)
{
    for (std::size_t i = 0; i < x; i++) {
        for (std::size_t j = 0; j < z; j++) {
            Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::GROUND, -1,
                {0.0f + (i * 55), 0.0f, 0.0f + (j * 55)}, sf::Color::Red, "./Assets/ground.stl");
        }
    }
}
