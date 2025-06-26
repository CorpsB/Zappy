/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Interpreter
*/

#pragma once

#include <iostream>
#include <unordered_map>
#include <regex>

#include "../../../3DRenderer/include/Renderer.hpp"

#define TILE_SIZE 70
#define OFFSET_FROM_GROUND -25.f
#define OFFSET_EYES_Y -1.5f

struct ResourceData {
    Renderer::PartType type;
    sf::Vector3f offset;
    sf::Color color;
    std::string assetPath;
    float yAdjust = -6.5f;
};

class Interpreter {
    public:
        Interpreter();
        ~Interpreter() {}

        /**
         * @brief Interprets the command received by the Client
         * @param data Command
         */
        void interpret(const std::string &data);
    private:
        std::unordered_map<std::string, std::pair<std::regex, std::function<void(const std::smatch &)>>> _instructions;

        std::array<ResourceData, 7> _resources;

        std::string _buffer;

        /**
         * @brief Determine the teams' color
         * @param teamColor Contains the color of each team
         * @param allTeamNames Contains the list of all team names
         * @param bigEnoughdiffColor If the color randomly generated is different enough from existing colors, return true
         */
        std::unordered_map<std::string, sf::Color> _teamColor;
        bool _bigEnoughDiffColor(sf::Color newColor);

        /**
         * @brief Set the map size
         * @param x Map width
         * @param y Map height
         */
        void _msz(const std::smatch &m);
        /**
         * @brief Display the content of a tile
         * @param x X Position of the tile
         * @param y Y Position of the tile
         * @param q0, q1, q2, q3, q4, q5, q6 Resources
         */
        void _bct(const std::smatch &m);
        /**
         * @brief Display the name of the team
         * @param m Must contain : teamName (std::string)
         */
        void _tna(const std::smatch &m);
        /**
         * @brief Spawn a new player
         * @param playerId ID of the new player
         * @param x X Position of the new player
         * @param y Y Position of the new player
         * @param orientation Orientation of the new player
         * @param level Level of the new player
         * @param teamName Team of the new player
         */
        void _pnw(const std::smatch &m);
        /**
         * @brief Set the position of a player
         * @param playerID ID of the player
         * @param x New X Position of the player
         * @param y New Y Position of the player
         * @param orientation New orientation of the player
         */
        void _ppo(const std::smatch &m);
        /**
         * @brief Kicks a player from the server
         * @param playerId ID of the player
         */
        void _plv(const std::smatch &m);
        void _pin(const std::smatch &m);
        void _pex(const std::smatch &m);
        void _pbc(const std::smatch &m);
        /**
         * @brief Starts an incantation (by the first player)
         * @param x X Position
         * @param y Y Position
         * @param level Level of the incantation
         * @param playersId Players involved in the incantation
         */
        void _pic(const std::smatch &m);
        /**
         * @brief Stops an incantation
         * @param x X Position
         * @param y Y Position
         * @param result Result of the incantation
         */
        void _pie(const std::smatch &m);
        void _pfk(const std::smatch &m); // Utile ?
        /**
         * @brief Drops resources
         * @param playerId ID of the player
         * @param resourceNumber Number of resources droped
         */
        void _pdr(const std::smatch &m);
        /**
         * @brief Collect resources
         * @param playerId ID of the player
         * @param resourceNumber Number of resources collected
         */
        void _pgt(const std::smatch &m);
        /**
         * @brief Despawn a player (death)
         * @param playerId ID of the player
         */
        void _pdi(const std::smatch &m);
        /**
         * @brief Lay an egg by a player
         * @param eggId ID of the egg
         * @param playerId ID of the player
         * @param x X Position
         * @param y Y Position
         */
        void _enw(const std::smatch &m);
        void _ebo(const std::smatch &m); // A Gardder ?
        /**
         * @brief Despawn an egg (death)
         * @param eggId ID of the egg
         */
        void _edi(const std::smatch &m);
        void _sgt(const std::smatch &m); // Utile ?
        void _sst(const std::smatch &m); // Utile ?
        /**
         * @brief Ends the game
         * @param teamName Winning team ?
         */
        void _seg(const std::smatch &m);
        void _smg(const std::smatch &m); // Utile ?
        void _suc(const std::smatch &m);
        void _sbp() {}
};
