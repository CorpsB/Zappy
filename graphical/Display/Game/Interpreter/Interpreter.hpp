/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Interpreter
*/

#pragma once

#include <iostream>

#include "../../../3DRenderer/include/Renderer.hpp"
#include "RegexMatches.hpp"

#define TILE_SIZE 70
#define OFFSET_FROM_GROUND -25.f
#define OFFSET_EYES_Y -1.5f

class Interpreter {
    public:
        Interpreter() {}
        ~Interpreter() {}

        /**
         * @brief Interprets the command received by the Client
         * @param data Command
         */
        void interpret(const std::string &data);
    private:
        /**
         * @brief Set the map size
         * @param x Map width
         * @param y Map height
         */
        void _msz(int x, int y);
        /**
         * @brief Display the content of a tile
         * @param x X Position of the tile
         * @param y Y Position of the tile
         * @param q0, q1, q2, q3, q4, q5, q6 Resources
         */
        void _bct(int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6);
        /**
         * @brief Spawn a new player
         * @param playerId ID of the new player
         * @param x X Position of the new player
         * @param y Y Position of the new player
         * @param orientation Orientation of the new player
         * @param level Level of the new player
         * @param teamName Team of the new player
         */
        void _tna(const std::string &teamName); // A garder ?
        void _pnw(int playerId, int x, int y, Renderer::Compass orientation, int level, std::string teamName);
        /**
         * @brief Set the position of a player
         * @param playerID ID of the player
         * @param x New X Position of the player
         * @param y New Y Position of the player
         * @param orientation New orientation of the player
         */
        void _ppo(int playerId, int x, int y, Renderer::Compass orientation);
        /**
         * @brief Kicks a player from the server
         * @param playerId ID of the player
         */
        void _plv(int playerId, int level);
        void _pin(int playerId, int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6); // A Garder ?
        void _pex(int playerId); // Utile ?
        void _pbc(int playerId, std::string msg); // Utile ?
        /**
         * @brief Starts an incantation (by the first player)
         * @param x X Position
         * @param y Y Position
         * @param level Level of the incantation
         * @param playersId Players involved in the incantation
         */
        void _pic(int x, int y, int level, std::vector<int> playersId);
        /**
         * @brief Stops an incantation
         * @param x X Position
         * @param y Y Position
         * @param result Result of the incantation
         */
        void _pie(int x, int y, std::string result);
        void _pfk(int playerId); // Utile ?
        /**
         * @brief Drops resources
         * @param playerId ID of the player
         * @param resourceNumber Number of resources droped
         */
        void _pdr(int playerId, int resourceNumber);
        /**
         * @brief Collect resources
         * @param playerId ID of the player
         * @param resourceNumber Number of resources collected
         */
        void _pgt(int playerId, int resourceNumber);
        /**
         * @brief Despawn a player (death)
         * @param playerId ID of the player
         */
        void _pdi(int playerId);
        /**
         * @brief Lay an egg by a player
         * @param eggId ID of the egg
         * @param playerId ID of the player
         * @param x X Position
         * @param y Y Position
         */
        void _enw(int eggId, int playerId, int x, int y);
        void _ebo(int eggId); // A Gardder ?
        /**
         * @brief Despawn an egg (death)
         * @param eggId ID of the egg
         */
        void _edi(int eggId);
        void _sgt(int timeUnit); // Utile ?
        void _sst(int timeUnit); // Utile ?
        /**
         * @brief Ends the game
         * @param teamName Winning team ?
         */
        void _seg(std::string teamName);
        void _smg(std::string msg); // Utile ?
        void _suc(std::string data);
        void _sbp() {}
};
