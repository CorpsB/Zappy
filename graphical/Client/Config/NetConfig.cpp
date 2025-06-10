/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** NetConfig
*/

#include "NetConfig.hpp"

const std::string &NetConfig::getIp() const
{
    return _ip;
}

const int &NetConfig::getPort() const
{
    return _port;
}

void NetConfig::setIp(const std::string &ip)
{
    _ip = ip;
}

void NetConfig::setPort(const int &port)
{
    _port = port;
}
