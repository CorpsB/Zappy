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
    if (_fds.fd != -1)
        closeSocket();
    _socket.sin_family = AF_INET;
    _socket.sin_port = htons(port);
    _socket.sin_addr.s_addr = inet_addr(ip.c_str());
    _fds.fd = socket(AF_INET, SOCK_STREAM, 0);
    _fds.events = POLLIN;
}

bool ai::network::Socket::readSocket()
{
    const auto start_time = std::chrono::high_resolution_clock::now();
    char local_buffer[READ_BUFFER_SIZE];
    int rd;

    while (_buffer.find('\n') == -1) {
        const auto end_time = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        if (duration.count() > READ_TIMEOUT) {
            closeSocket();
            throw utils::exception::Error("CONNECTION", _thread_name + " Socket receive timeout (" + std::to_string(READ_TIMEOUT) + "s).");
        }
        if (!isServerReadable())
            continue;
        memset(local_buffer, 0, READ_BUFFER_SIZE);
        rd = read(_fds.fd, local_buffer, READ_BUFFER_SIZE);
        if (rd < 0) {
            closeSocket();
            throw utils::exception::Error("CONNECTION", _thread_name + " Read failure.");
        }
        _buffer.append(local_buffer, rd);
    }
    return true;
}

std::string ai::network::Socket::readSocketBuffer()
{
    if (!readSocket())
        return "dead";
    for (size_t pos = _buffer.find("\n"); pos != std::string::npos;
    pos = _buffer.find("\n")) {
        std::string line = _buffer.substr(0, pos);

        _buffer.erase(0, pos + 2);
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

bool ai::network::Socket::isServerReadable()
{
    const int queue = poll((struct pollfd *)&_fds, 1, 0);

    if (queue < 0)
        throw utils::exception::Error("CONNECTION", _thread_name + " Poll failure.");
    if (queue == 0)
        return false;
    if (_fds.revents & POLLIN)
        return true;
    return false;
}

void ai::network::Socket::connectServer()
{
    if (connect(_fds.fd, (struct sockaddr*)&_socket, sizeof(_socket)) < 0)
        throw utils::exception::Error("CONNECTION", _thread_name + " Failed to join the server.");
}

void ai::network::Socket::greetsServer()
{
    const std::string welcome_msg = readSocketBuffer();
    if (welcome_msg != "WELCOME")
        throw utils::exception::Error("CONNECTION", _thread_name + " The server didn't greet us. What a bad guy.");

    try {
        sendCommand(_team_name);
    } catch (std::exception e) {
        throw utils::exception::Error("CONNECTION", _thread_name + " Failed to send team name.");
    }

    const std::string client_num = readSocketBuffer();
    if (client_num == "dead")
        throw utils::exception::Error("CONNECTION", _thread_name + " Failed receiving client slot info.");
    if (client_num == "ko")
        throw utils::exception::Error("CONNECTION", _thread_name + " Team name rejected or team full : " + client_num);

    const int available_slots = std::atoi(client_num.c_str());
    if (!utils::validation::integer(available_slots, client_num))
        throw utils::exception::Error("CONNECTION", _thread_name + " Expected client slots (number) or 'ko', got '" + client_num + "'");

    const std::string world_size = readSocketBuffer();
    if (world_size == "dead")
        throw utils::exception::Error("CONNECTION", _thread_name + " Failed to receive world size.");
}

void ai::network::Socket::sendCommand(const std::string &cmd)
{
    const std::string cmd_final = cmd + "\n";

    if (write(_fds.fd, cmd_final.c_str(), cmd_final.size()) < 0)
        throw utils::exception::Error("CONNECTION", _thread_name + " Socket error while sending '" + cmd + "'");
}

std::string ai::network::Socket::doAction(const std::string &cmd)
{
    sendCommand(cmd);
    return readSocketBuffer();
}
