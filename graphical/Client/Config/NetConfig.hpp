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
         * @brief Retrieves the currently configured IP address.
         *
         * @return A constant reference to the IP address string.
         */
        const std::string &getIp() const;
        /**
         * @brief Retrieves the currently configured port number.
         *
         * @return A constant reference to the port number.
         */
        const int &getPort() const;

        /**
         * @brief Sets the IP address for the client.
         *
         * Stores the given string as the new IP address for network connection.
         *
         * @param ip The IP address to set (as a string).
         */
        void setIp(const std::string &ip);
        /**
         * @brief Sets the port number for the client.
         *
         * Stores the given integer as the port to use when connecting to the server.
         *
         * @param port The port number to set.
         */
        void setPort(const int &port);

        /**
         * @brief Parses command-line arguments to extract the IP address and port.
         *
         * Accepts `-h <ip>` for host and `-p <port>` for port number. Ensures validity using
         * internal parsing functions. Logs specific error messages if invalid or missing arguments are found.
         *
         * @param ac Argument count (from main).
         * @param av Argument values (from main).
         * @return False if arguments are valid and stored, true if any parsing error occurred.
         */
        bool parseArgs(int ac, char **av);
    private:
        std::string _ip;
        int _port;

        /**
         * @brief Validates and sets the given IP address.
         *
         * Uses a regular expression to ensure the provided IP address is a valid IPv4 format.
         *
         * @param ip The IP address string to validate and store.
         * @return True if the IP is invalid, false if it is valid and stored.
         */
        bool _parseIp(const std::string &ip);
        /**
         * @brief Validates and sets the given port number.
         *
         * Uses regex and size checks to ensure the port is numeric and within the allowed range (0–65535).
         *
         * @param port The port number as a string to validate and store.
         * @return True if the port is invalid, false if it is valid and stored.
         */
        bool _parsePort(const std::string &port);
};
