/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** NetConfig
*/

#pragma once

#include <iostream>
#include <sys/socket.h>
#include <poll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>

class NetConfig {
    public:
        NetConfig() {};
        ~NetConfig() = default;

        const std::string &getIp() const;
        const int &getPort() const;

        void setIp(const std::string &ip);
        void setPort(const int &port);
    private:
        std::string _ip;
        int _port;
};
