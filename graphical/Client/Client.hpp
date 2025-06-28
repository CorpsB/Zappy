/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Client
*/

/**
 * @file Client.hpp
 * @brief Déclaration de la classe Client du projet Zappy.
 *
 * Cette classe représente le client principal du jeu Zappy. Elle gère
 * l'ensemble de la communication réseau avec le serveur : initialisation
 * de la socket, lecture/écriture, gestion de la connexion, et boucle de jeu.
 *
 * Le Client encapsule également la configuration réseau (`NetConfig`) et
 * fournit une interface simple pour interagir avec le serveur de jeu
 * en utilisant une instance unique (singleton).
 *
 * @author Thomas Camuset
 * @date 2025
 * @version 1.1
 * @see Game, NetConfig
 */

#pragma once

#include "../Display/Game/Game.hpp"

#include "Config/NetConfig.hpp"

class Client {
    public:
        Client() {};
        ~Client();

        static Client &GetInstance();

        /**
         * @brief Setup the socket
         */
        void initSocket();
        /**
         * @brief Close the socket and end the client
         */
        void closeSocket();
        /**
         * @brief Read the data sent by the server
         * @return Returns the line received
         */
        std::string readSocket() const;

        /**
         * @brief Connect the client to the server
         * @return 'true' if success and 'false' if not
         */
        bool connectToServer();
        /**
         * @brief Send a command to the server
         * @param msg Command to send
         */
        void sendToServer(const std::string &msg) const;
        /**
         * @brief Run the loop of the client
         * @param game The Game instance to call & modify
         */
        void run(Game &game);

        NetConfig &getConfig();
    private:
        NetConfig _config;

        int _fd;
        struct pollfd _fds;
        struct sockaddr_in _addr;
};
