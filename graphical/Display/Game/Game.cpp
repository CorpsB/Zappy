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
    _window.init(1280, 720);
    if (!Renderer::initRenderer(_window.getWindow())) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return;
    }
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
    std::cerr << "Instruction : " << data << std::endl;
    _interpreter.interpret(data);
}
