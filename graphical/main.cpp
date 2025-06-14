/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** main graphic
*/

#include "Window.hpp"
#include "Event.hpp"
#include "Client/Client.hpp"

#include <thread>
#include <chrono>

#include "3DRenderer/include/Renderer.hpp"
#include <SFML/System/Clock.hpp>
#include <iostream>

void runDisplay()
{
    Window window;
    Event event;
    
    window.init(1280, 720);
    if (!Renderer::initRenderer(window.getWindow())) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return;
    }

    // Spawn un golem Bricien
    Renderer::rotatingEntityId = Renderer::spawn(Renderer::EntityType::STL,
        {0.0f, 0.0f, 5.0f}, sf::Color::Cyan, "./Assets/body_golem.stl");

    sf::Clock clock;
    while (event.getEvent(window.getWindow()) != -1) {
        float dt = clock.restart().asSeconds();
        if (dt <= 0) continue;
        window.clear();
        Renderer::update(dt);
        Renderer::render(dt, window.getWindow());
        window.display();
    }
    window.stop();
}

void runNetwork()
{
    Client &client = Client::GetInstance();

    client.initSocket();
    while (!client.connectToServer())
        std::this_thread::sleep_for(std::chrono::seconds(1));
    client.run();
    client.closeSocket();
}

// int main(int ac, char **av)
int main()
{
    // Client &client = Client::GetInstance();

    // if (client.getConfig().parseArgs(ac - 1, av + 1))
    //     return 84;
    // std::thread networkInstance(runNetwork);
    // networkInstance.join();
    runDisplay();
    return 0;
}
