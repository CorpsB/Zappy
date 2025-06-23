/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Client
*/

#include "Client.hpp"

Client &Client::GetInstance()
{
    static Client _client;

    return _client;
}

Client::~Client()
{
    closeSocket();
}

void Client::initSocket()
{
    if (_fds.fd != -1)
        closeSocket();
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_config.getPort());
    _addr.sin_addr.s_addr = inet_addr(_config.getIp().c_str());
    _fds.fd = socket(AF_INET, SOCK_STREAM, 0);
    _fds.events = POLLIN;
}

void Client::closeSocket()
{
    if (_fds.fd != -1) {
        close(_fds.fd);
        _fds.fd = -1;
    }
    _fds.events = 0;
}

std::string Client::readSocket() const
{
    std::array<char, BUFFER_SIZE> buffer {};
    int rd = read(_fds.fd, buffer.data(), BUFFER_SIZE - 1);

    if (rd > 0)
        return std::string(buffer.data(), rd);
    else if (rd == 0)
        std::cerr << "Server closed." << std::endl;
    else
        std::cerr << "Read failure." << std::endl;
    return "";
}

bool Client::connectToServer()
{
    if (connect(_fds.fd, (struct sockaddr*) &_addr, sizeof(_addr)) < 0) {
        std::cerr << "Failed to connect to the server." << std::endl;
        return false;
    }
    sendToServer("GRAPHIC\n");
    return true;
}

void Client::sendToServer(const std::string &msg) const
{
    if (send(_fds.fd, msg.c_str(), msg.size(), 0) < 0)
        std::cerr << "Failed to send : " << msg << std::endl;
}

void Client::run(Game &game)
{
    int queue;
    std::string data;

    while (1) {
        // std::cerr << "Hi there ! How's it going ?" << std::endl;
        queue = poll((struct pollfd *) &_fds, 1, 0);
        if (queue < 0) {
            std::cerr << "Poll failure." << std::endl;
            break;
        }
        if (queue == 0)
            continue;
        if (_fds.revents & POLLIN) {
            data = readSocket();
            if (data == "") {
                closeSocket();
                std::cerr << "What the fuck ?" << std::endl;
                break;
            }
            game.processData(data);
        }
    }
    std::cerr << "WHYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY !?" << std::endl;
}

NetConfig &Client::getConfig()
{
    return _config;
}
