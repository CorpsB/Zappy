/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** NetConfig
*/

/**
 * @file NetConfig.hpp
 * @brief Déclaration de la classe NetConfig pour la configuration réseau du client Zappy.
 *
 * Cette classe gère la configuration réseau du client, notamment l'adresse IP
 * et le port du serveur. Elle offre une interface simple pour définir et
 * valider ces paramètres, à partir de la ligne de commande ou manuellement.
 *
 * Elle encapsule également la validation des entrées utilisateur via des expressions
 * régulières (regex) pour l’adresse IP, et s’assure que le port est dans les bornes valides.
 *
 * Constantes :
 * - `BUFFER_SIZE` : taille maximale de lecture d’un message.
 * - `MAX_PORT` : port maximal autorisé (65535).
 * - `MAX_PORT_SIZE` : taille max pour la représentation texte d’un port.
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
