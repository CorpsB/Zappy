/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** main
*/

#include "Renderer.hpp"
#include <SFML/System/Clock.hpp>
#include <iostream>

int main() {
    if (!Renderer::initRenderer(1280, 720, "ZappyZe")) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return -1;
    }

    // Spawn un golem Bricien
    Renderer::rotatingEntityId = Renderer::spawn(Renderer::EntityType::STL,
        {0.0f, 0.0f, 5.0f}, sf::Color::Cyan, "./Assets/body_golem.stl");

    sf::Clock clock;
    while (Renderer::getIsRunning()) {
        float dt = clock.restart().asSeconds();
        if (dt <= 0) continue;
        Renderer::update(dt);
        Renderer::render(dt);
    }

    Renderer::shutdownRenderer();
    return 0;
}