/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Client
*/

/**
 * @file Client.hpp
 * @brief Declaration of the Client class for the Zappy project.
 *
 * This class represents the main client of the Zappy game. It handles
 * all network communication with the server: socket initialization,
 * reading/writing, connection management, and the main execution loop.
 *
 * The Client also encapsulates network configuration (`NetConfig`) and
 * provides a simple interface to interact with the game server
 * using a unique instance (singleton pattern).
 *
 * @author Thomas Camuset
 * @date 2025
 * @version 1.1
 * @see Game, NetConfig
 */

#pragma once

#include "../Display/Game/Game.hpp"

#include "Config/NetConfig.hpp"

class Client {
    public:
        Client() {};
        ~Client();

        /**
         * @brief Retrieves the singleton instance of the Client.
         *
         * Ensures that only one Client object exists throughout the application lifecycle.
         *
         * @return A reference to the unique Client instance.
         */
        static Client &GetInstance();

        /**
         * @brief Initializes the client socket and sets up poll configuration.
         *
         * Configures the address structure using values from NetConfig and creates a TCP socket.
         * If a previous socket is open, it is closed before initializing a new one.
         */
        void initSocket();
        /**
         * @brief Closes the client socket and resets poll event flags.
         *
         * Ensures safe shutdown of the connection and avoids resource leaks.
         */
        void closeSocket();
        /**
         * @brief Reads incoming data from the server socket.
         *
         * Uses a fixed-size buffer and returns the received string.
         * Also handles disconnection or read errors with appropriate logging.
         *
         * @return The string received from the server, or an empty string on error/disconnect.
         */
        std::string readSocket() const;

        /**
         * @brief Attempts to connect to the server using the configured address.
         *
         * Sends the initial handshake string ("GRAPHIC") upon successful connection.
         *
         * @return True if the connection was successful, false otherwise.
         */
        bool connectToServer();
        /**
         * @brief Sends a command to the server over the socket.
         *
         * Logs a warning if the send operation fails.
         *
         * @param msg The message to send (e.g., a command or response).
         */
        void sendToServer(const std::string &msg) const;
        /**
         * @brief Main execution loop for the client.
         *
         * Uses `poll()` to monitor the socket for incoming data.
         * When data is available, it reads and forwards it to the Game logic.
         * Terminates the loop on disconnection or poll failure.
         *
         * @param game The Game instance that handles server data.
         */
        void run(Game &game);

        /**
         * @brief Retrieves the current network configuration used by the client.
         *
         * @return Reference to the internal NetConfig instance.
         */
        NetConfig &getConfig();
    private:
        NetConfig _config;

        int _fd;
        struct pollfd _fds;
        struct sockaddr_in _addr;
};
