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

bool NetConfig::_parseIp(const std::string &ip)
{
    static const std::regex ipv4Pattern(R"(^(25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})(\.(25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})){3}$)");

    if (!std::regex_match(ip, ipv4Pattern)) {
        std::cerr << "Invalid IP argument" << std::endl;
        return true;
    }
    _ip = ip;
    return false;
}

bool NetConfig::_parsePort(const std::string &port)
{
    int iport = 0;
    static const std::regex portPattern(R"(\d{1,5})");

    if (port.size() > MAX_PORT_SIZE) {
        std::cerr << "Invalid PORT argument" << std::endl;
        return true;
    }
    if (!std::regex_match(port, portPattern)) {
        std::cerr << "Invalid PORT argument" << std::endl;
        return true;
    }
    iport = std::stoi(port);
    if (iport > MAX_PORT) {
        std::cerr << "Invalid PORT argument" << std::endl;
        return true;
    }
    _port = iport;
    return false;
}

bool NetConfig::parseArgs(int ac, char **av)
{
    bool error = false;

    for (int i = 0; i < ac && !error; i++) {
        if (av[i][0] == '-') {
            if (av[i][1] == 'h' && (i + 1) < ac) {
                error = _parseIp(av[i + 1]);
                i++;
                continue;
            } else if (av[i][1] == 'p' && (i + 1) < ac) {
                error = _parsePort(av[i + 1]);
                i++;
                continue;
            }
        }
        std::cerr << "Invalid argument" << std::endl;
        error = true;
    }
    if (_ip == "") {
        std::cerr << "Missing argument : -h" << std::endl;
        error = true;
    }
    if (_port == -1) {
        std::cerr << "Missing argument : -p" << std::endl;
        error = true;
    }
    if (!error)
        return false;
    std::cerr << "Usage: ./zappy_gui -h <host> -p <port>" << std::endl;
    return true;
}
