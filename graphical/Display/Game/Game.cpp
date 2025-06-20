/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Game
*/

#include "Game.hpp"

Game &Game::GetInstance()
{
    static Game _game;

    return _game;
}

// One piece of ground has sides of about 55 px
void Game::init()
{
    // int size_grid = 4;

    _window.init(1280, 720);
    if (!Renderer::initRenderer(_window.getWindow())) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return;
    }
    // Spawn un golem Bricien
    // Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::BODY, 4040,
    //     {0.0f, -25.0f, 0.0f}, sf::Color::Cyan, "./Assets/body_golem.stl", Renderer::Compass::NORTH);
    // Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::BODY, 4042,
    //     {55.0f, -25.0f, 0.0f}, sf::Color::Cyan, "./Assets/body_golem.stl", Renderer::Compass::SOUTH);
    // // 4040 = client id
    // Renderer::rotatingEntityId = Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::EYES, 4040,
    //     {0.0f, -25.0f + -1.5f, 0.0f + -6.5f}, sf::Color::Black, "./Assets/eyes_golem.stl");
    // Renderer::rotatingEntityId = Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::EYES, 4042,
    //     {55.0f, -25.0f + -1.5f, 0.0f + -6.5f}, sf::Color::Black, "./Assets/eyes_golem.stl");
    // for (int x = 0; x < size_grid; x++) {
    //     for (int z = 0; z < size_grid; z++)
    //         //-1 -> not a client, just an entity that won't move
    //         Renderer::rotatingEntityId = Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::GROUND, -1,
    //             {0.0f + (x * 55), 0.0f, 0.0f + (z * 55)}, sf::Color::Red, "./Assets/ground.stl");
    // }
}

void Game::run()
{
    sf::Clock clock;
    while (_event.getEvent(_window.getWindow()) != -1) {
        float dt = clock.restart().asSeconds();
        if (dt <= 0) continue;
        _window.clear();
        Renderer::update(dt);
        Renderer::render(dt, _window.getWindow());
        _window.display();
    }
}

void Game::stop()
{
    _window.stop();
}

void Game::processData(const std::string &data)
{
    _interpreter.interpret(_hud, data);
}
