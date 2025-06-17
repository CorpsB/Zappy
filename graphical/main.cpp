/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** main graphic
*/

#include "Display/Window/Window.hpp"
#include "Display/Event/Event.hpp"
#include "Client/Client.hpp"
#include "Display/Game/Game.hpp"

#include <thread>
#include <chrono>

#include <SFML/System/Clock.hpp>
#include <iostream>

void runDisplay()
{
    Game &game = Game::GetInstance();

    game.init();
    game.run();
    game.stop();
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

int main(int ac, char **av)
// int main()
{
    Client &client = Client::GetInstance();

    if (client.getConfig().parseArgs(ac - 1, av + 1))
        return 84;
    std::thread networkInstance(runNetwork);
    std::thread displayInstance(runDisplay);
    networkInstance.join();
    displayInstance.join();
    return 0;
}
