/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Socket
*/

#include "Socket.hpp"
#include "../utils/utils.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cstring>

ai::network::Socket::Socket()
{
    _thread_name = "";
    _team_name = "";
    _buffer = "";
}

void ai::network::Socket::setup(const std::string &thread_name, const std::string &team_name)
{
    _thread_name = thread_name;
    _team_name = team_name;
    _buffer = "";
}

void ai::network::Socket::initSocket(int port, const std::string &ip)
{
    _socket.sin_family = AF_INET;
    _socket.sin_port = htons(port);
    _socket.sin_addr.s_addr = inet_addr(ip.c_str());
    _fds.fd = socket(AF_INET, SOCK_STREAM, 0);
    _fds.events = POLLIN;
}

bool ai::network::Socket::readSocket(int timeout)
{
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
    const auto start_time = std::chrono::high_resolution_clock::now();
    char local_buffer[READ_BUFFER_SIZE];
    int rd;

    while (_buffer.find('\n') == -1) {
        const auto end_time = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        if (duration.count() > timeout) {
            closeSocket();
            logger.log("[Error] Socket receive timeout (" + std::to_string(timeout) + "ms).");
            return false;
        }
        switch (isServerReadable()) {
            case 1:
                memset(local_buffer, 0, READ_BUFFER_SIZE);
                rd = read(_fds.fd, local_buffer, READ_BUFFER_SIZE);
                if (rd < 0) {
                    closeSocket();
                    logger.log("[Error] Read failure.");
                    return false;
                }
                _buffer.append(local_buffer, rd);
                break;
            case 2:
                closeSocket();
                logger.log("[Error] Poll failure.");
                return false;
            default:
                break;
        }
    }
    return true;
}

std::string ai::network::Socket::readSocketBuffer(int timeout)
{
    if (!readSocket(timeout))
        return "dead";
    for (size_t pos = _buffer.find("\n"); pos != std::string::npos;
    pos = _buffer.find("\n")) {
        std::string line = _buffer.substr(0, pos);

        _buffer.erase(0, pos + 1);
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        if (!line.empty())
            return line;
    }
    return "dead";
}

void ai::network::Socket::closeSocket()
{
    if (_fds.fd != -1) {
        close(_fds.fd);
        _fds.fd = -1;
    }
    _fds.events = 0;
}

int ai::network::Socket::isServerReadable()
{
    const int queue = poll((struct pollfd *)&_fds, 1, 0);

    if (queue < 0)
        return 2;
    if (queue == 0)
        return 0;
    if (_fds.revents & POLLIN)
        return 1;
    return 0;
}

void ai::network::Socket::connectServer()
{
    if (connect(_fds.fd, (struct sockaddr*)&_socket, sizeof(_socket)) < 0)
        throw utils::exception::Error("CONNECTION", "Failed to join the server.");
}

void ai::network::Socket::greetsServer()
{
    const std::string welcome_msg = readSocketBuffer();
    if (welcome_msg != "WELCOME")
        throw utils::exception::Error("CONNECTION", "The server didn't greet us. What a bad guy.");

    try {
        sendCommand(_team_name);
    } catch (...) {
        throw utils::exception::Error("CONNECTION", "Failed to send team name.");
    }

    const std::string client_num = readSocketBuffer();
    if (client_num == "dead")
        throw utils::exception::Error("CONNECTION", "Failed receiving client slot info.");
    if (client_num == "ko")
        throw utils::exception::Error("CONNECTION", "Team name rejected or team full : " + client_num);

    const int available_slots = std::atoi(client_num.c_str());
    if (!utils::validation::integer(available_slots, client_num))
        throw utils::exception::Error("CONNECTION", "Expected client slots (number) or 'ko', got '" + client_num + "'.");

    const std::string world_size = readSocketBuffer();
    if (world_size == "dead")
        throw utils::exception::Error("CONNECTION", "Failed to receive world size.");
}

bool ai::network::Socket::sendCommand(const std::string &cmd)
{
    const std::string cmd_final = cmd + "\n";

    if (write(_fds.fd, cmd_final.c_str(), cmd_final.size()) < 0) {
        utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
        logger.log("[Error] Socket error while sending '" + cmd + "'.");
        return false;
    }
    return true;
}

std::string ai::network::Socket::doAction(const std::string &cmd, int timeout)
{
    if (cmd != "") {
        if (!sendCommand(cmd))
            return "dead";
    }
    return readSocketBuffer(timeout);
}
