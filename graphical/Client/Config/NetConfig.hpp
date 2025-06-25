/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** NetConfig
*/

#pragma once

#define BUFFER_SIZE 1024
#define MAX_PORT 65535
#define MAX_PORT_SIZE 5

#include <iostream>
#include <sys/socket.h>
#include <poll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <array>
#include <regex>

class NetConfig {
    public:
        NetConfig() : _ip(""), _port(-1) {};
        ~NetConfig() = default;

        const std::string &getIp() const;
        const int &getPort() const;

        void setIp(const std::string &ip);
        void setPort(const int &port);

        bool parseArgs(int ac, char **av);
    private:
        std::string _ip;
        int _port;

        bool _parseIp(const std::string &ip);
        bool _parsePort(const std::string &port);
};
