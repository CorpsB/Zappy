/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Game
*/

/**
 * @file Game.cpp
 * @brief Implementation of the Game class, the main runtime loop for the Zappy graphical client.
 *
 * This file defines the methods of the `Game` class, which acts as the central controller
 * for the client-side runtime. It manages the game window, the 3D renderer, and the event
 * processing loop using SFML.
 *
 * The `run()` method handles the main frame loop, rendering logic, event polling, and update
 * ticks. It ensures proper coordination between the `Renderer`, `Event`, and `Interpreter`
 * components of the application.
 *
 * The class follows the singleton pattern and provides global access to its instance
 * through `Game::GetInstance()`. It also relays server messages to the `Interpreter`
 * for real-time in-game updates.
 *
 * @author Thomas Camuset
 * @date 2025
 * @version 1.0
 * @see Game.hpp, Renderer, Interpreter, Event, Window
 */

#include "Game.hpp"

Game &Game::GetInstance(std::shared_ptr<Renderer::Renderer> renderer, std::shared_ptr<Renderer::EntityClass> entity)
{
    static Game _game(renderer, entity);

    return _game;
}

void Game::init(std::shared_ptr<Renderer::Renderer> renderer, std::shared_ptr<Renderer::EntityClass> entity)
{
    this->_renderer = renderer;
    _window.init(1280, 720);
    if (!_renderer.get()->initRenderer(_window.getWindow(), entity)) {
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
        _renderer.get()->update(dt, _window.getWindow());
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

std::shared_ptr<Renderer::EntityClass> Game::getEntity() const
{
    return this->_entity;

}
