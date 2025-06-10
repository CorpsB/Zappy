/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Client
*/

#pragma once

#include "Config/NetConfig.hpp"

class Client {
    public:
        Client() {};
        ~Client() = default;

        const NetConfig &getConfig();
    private:
        NetConfig _config;

        int _fd;
        struct pollfd _fds;
        struct sockaddr_in _addr;
};
