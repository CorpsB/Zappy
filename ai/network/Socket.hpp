/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Socket
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
    class Socket {
        public:
            Socket();
            ~Socket() = default;

            void setup(const std::string &thread_name, const std::string &team_name);
            void initSocket(int port, const std::string &ip);
            bool readSocket();
            std::string readSocketBuffer();
            void closeSocket();

            int isServerReadable();
            void connectServer();
            void greetsServer();

            bool sendCommand(const std::string &cmd);
            std::string doAction(const std::string &cmd);

        private:
            struct pollfd _fds;
            struct sockaddr_in _socket;
            std::string _buffer;
            std::string _thread_name;
            std::string _team_name;
    };
}
