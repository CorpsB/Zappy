/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Socket
*/

/**
 * @file Socket.hpp
 * @brief Provides a TCP socket wrapper for communicating with the Zappy server.  
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @details
 * Encapsulates socket creation, connection, polling for data, sending commands,
 * and reading responses with timeout handling.
 */

#pragma once

#define READ_TIMEOUT 30000
#define READ_BUFFER_SIZE 2048

#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

namespace ai::network
{
    /**
     * @class Socket
     * @brief Manages a single TCP connection to the Zappy server.
     */
    class Socket {
        public:
            /**
             * @brief Constructs a new Socket and initializes internal state.
             */
            Socket();

            /**
             * @brief Destroys the Socket, closing any open descriptor.
             */
            ~Socket() = default;

            /**
             * @brief Sets up thread and team identifiers for logging.
             * @param thread_name Name prefix for log messages.
             * @param team_name   Team identifier sent to server after connection.
             */
            void setup(const std::string &thread_name, const std::string &team_name);

            /**
             * @brief Creates and configures the socket descriptor.
             * @param port Port number of the server.
             * @param ip   IPv4 address of the server.
             */
            void initSocket(int port, const std::string &ip);

            /**
             * @brief Reads from socket until a newline is received or timeout.
             * @return true if data received before timeout, false on error/timeout.
             */
            bool readSocket();

            /**
             * @brief Extracts a single line from the internal read buffer.
             * @return The next line without newline, or "dead" on failure.
             */
            std::string readSocketBuffer();

            /**
             * @brief Closes the socket and resets poll events.
             */
            void closeSocket();

            /**
             * @brief Polls the socket to check readability.
             * @return 1 if data available, 0 if none, 2 on poll error.
             */
            int isServerReadable();

            /**
             * @brief Establishes a TCP connection to the configured server.
             * @throws ai::utils::exception::Error on failure.
             */
            void connectServer();

            /**
             * @brief Performs initial handshake: reads welcome, sends team name, reads slot count.
             * @throws ai::utils::exception::Error on protocol violation or errors.
             */
            void greetsServer();

            /**
             * @brief Sends a command string over the socket, appending newline.
             * @param cmd The command to send (without newline).
             * @return true if fully sent, false on write error.
             */
            bool sendCommand(const std::string &cmd);

            /**
             * @brief Optionally sends a command, then reads and returns the server response.
             * @param cmd The command to perform (empty to only read).
             * @return Server response line, or "dead" on error.
             */
            std::string doAction(const std::string &cmd);

        private:
            struct pollfd    _fds;         // poll descriptor for socket
            struct sockaddr_in _socket;    // server address info
            std::string      _buffer;      // accumulated read data
            std::string      _thread_name; // logging prefix
            std::string      _team_name;   // team identifier sent to server
    };
}
