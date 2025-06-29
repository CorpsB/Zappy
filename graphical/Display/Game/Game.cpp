/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(std::shared_ptr<Renderer::Renderer> renderer)
    : _interpreter(renderer), _renderer(renderer)
{
}

Game &Game::GetInstance(std::shared_ptr<Renderer::Renderer> renderer)
{
    static Game _game(renderer);

    return _game;
}

void Game::init(std::shared_ptr<Renderer::Renderer> renderer)
{
    this->_renderer = renderer;
    _window.init(1280, 720);
    if (!_renderer.get()->initRenderer(_window.getWindow())) {
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
        _renderer.get()->update(dt);
        _renderer.get()->render(dt, _window.getWindow());
        _window.display();
    }
}

void Game::stop()
{
    _window.stop();
}

void Game::processData(const std::string &data)
{
    _interpreter.interpret(data);
}

std::shared_ptr<Renderer::Renderer> Game::getRenderer() const
{
    return this->_renderer;
}
