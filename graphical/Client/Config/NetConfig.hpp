/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** NetConfig
*/

/**
 * @file NetConfig.hpp
 * @brief Declaration of the NetConfig class for Zappy client's network configuration.
 *
 * This class manages the client's network configuration, including the server's IP
 * address and port. It provides a simple interface to set and validate these parameters,
 * either manually or by parsing command-line arguments.
 *
 * It also encapsulates validation of user input using regular expressions (regex)
 * for the IP address, and ensures the port number falls within a valid range.
 *
 * Constants:
 * - `BUFFER_SIZE`: maximum size for reading a message.
 * - `MAX_PORT`: maximum allowed port value (65535).
 * - `MAX_PORT_SIZE`: maximum length for a port in string form.
 *
 * @author Thomas Camuset
 * @date 2025
 * @version 1.0
 * @see Client
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

        /**
         * @brief Returns the ip address as a std::string
         * @return IP address
         */
        const std::string &getIp() const;
        /**
         * @brief Returns the port as a std::string
         * @return Port
         */
        const int &getPort() const;

        /**
         * @brief Set the IP address
         * @param ip IP address to set
         */
        void setIp(const std::string &ip);
        /**
         * @brief Set the port value
         * @param port Port to set
         */
        void setPort(const int &port);

        /**
         * @brief Parse starting arguments
         * @param ac Number of arguments
         * @param av List of arguments
         * @return Returns 'true' if the parsing was successful or 'false' otherwise
         */
        bool parseArgs(int ac, char **av);
    private:
        std::string _ip;
        int _port;

        /**
         * @brief Parse the real pattern of an IP address
         * @param ip IP address (std::string)
         * @return Returns 'true' if the parsing was successful or 'false' otherwise
         */
        bool _parseIp(const std::string &ip);
        /**
         * @brief Parse the real pattern of a Port
         * @param port Port (std::string)
         * @return Returns 'true' if the parsing was successful or 'false' otherwise
         */
        bool _parsePort(const std::string &port);
};
