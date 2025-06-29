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

/**
 * @brief Starts the graphical display thread.
 *
 * Initializes and runs the main game loop (rendering, events, updates).
 *
 * @param game Reference to the shared Game instance.
 */
void runDisplay(Game &game)
{
    game.init(game.getRenderer());
    game.run();
    game.stop();
}

/**
 * @brief Starts the network communication thread.
 *
 * Initializes the client socket, attempts to connect to the server (with retry),
 * and starts listening to server messages to forward them to the game logic.
 *
 * @param game Reference to the shared Game instance.
 */
void runNetwork(Game &game)
{
    Client &client = Client::GetInstance();

    client.initSocket();
    while (!client.connectToServer())
        std::this_thread::sleep_for(std::chrono::seconds(1));
    client.run(game);
    client.closeSocket();
}

/**
 * @brief Entry point of the Zappy graphical client.
 *
 * This function initializes the game and network systems using a shared `Game` instance.
 * It parses command-line arguments, then launches two threads:
 * - `runDisplay`: manages window rendering and event handling.
 * - `runNetwork`: manages the connection with the Zappy server.
 *
 * Both threads are joined before the application exits.
 *
 * @param ac Argument count.
 * @param av Argument values.
 * @return 0 on success, 84 if argument parsing fails.
 */
int main(int ac, char **av)
{
    Client &client = Client::GetInstance();
    Game &game = Game::GetInstance(std::make_shared<Renderer::Renderer>());

    if (client.getConfig().parseArgs(ac - 1, av + 1))
        return 84;
    std::thread networkInstance(runNetwork, std::ref(game));
    std::thread displayInstance(runDisplay, std::ref(game));
    networkInstance.join();
    displayInstance.join();
    return 0;
}
