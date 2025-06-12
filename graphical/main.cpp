/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** main graphic
*/

#include "Window/Window.hpp"
#include "Event/Event.hpp"
#include "Client/Client.hpp"

#include <thread>
#include <chrono>

void runDisplay()
{
    // A faire
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
{
    Client &client = Client::GetInstance();

    if (client.getConfig().parseArgs(ac - 1, av + 1))
        return 84;
    std::thread networkInstance(runNetwork);
    networkInstance.join();
    return 0;
}
