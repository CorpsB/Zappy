/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Client
*/

#pragma once

#include "../Display/Game/Game.hpp"

#include "Config/NetConfig.hpp"

class Client {
    public:
        Client() {};
        ~Client() = default;

        static Client &GetInstance();

        void initSocket();
        void closeSocket();
        std::string readSocket() const;

        bool connectToServer();
        void sendToServer(const std::string &msg) const;
        void run(Game &game);

        NetConfig &getConfig();
    private:
        NetConfig _config;

        int _fd;
        struct pollfd _fds;
        struct sockaddr_in _addr;
};
