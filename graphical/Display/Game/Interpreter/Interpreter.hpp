/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Interpreter
*/

/**
 * @file Interpreter.hpp
 * @brief Declaration of the Interpreter class used to parse and handle server instructions for the Zappy client.
 *
 * The Interpreter class is responsible for decoding and executing textual commands sent
 * by the Zappy server. It maps regex-based patterns to dedicated handler methods, each one
 * implementing a specific server-side instruction (such as spawning players, updating tiles,
 * displaying broadcasts, etc.).
 *
 * This class interacts directly with the 3D `Renderer` module to trigger visual updates in the
 * graphical client, such as entity animations, color updates, or tile content rendering.
 *
 * It uses a shared `Renderer` instance to manipulate 3D elements and maintains internal data
 * like resources, team colors, and an input buffer. The matching system is extensible, using
 * an unordered map of regex patterns and corresponding lambdas or bound methods.
 *
 * Constants:
 * - `TILE_SIZE`: Size of each tile on the map in 3D units.
 * - `OFFSET_FROM_GROUND`: Y-axis offset for ground positioning.
 * - `OFFSET_EYES_Y`: Camera/player viewpoint vertical offset.
 *
 * @author Thomas Camuset
 * @date 2025
 * @version 1.0
 * @see Renderer, sf::Color, std::regex
 * @note This system can be extended by adding new regex-command pairs to `_instructions`.
 */

#pragma once

#include <iostream>
#include <unordered_map>
#include <regex>
#include <random>
#include <memory>

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
        Interpreter(std::shared_ptr<Renderer::Renderer> renderer);
        ~Interpreter() = default;

        /**
         * @brief Interprets the command received by the Client
         * @param data Command
         */
        void interpret(const std::string &data);
    private:
        std::unordered_map<std::string, std::pair<std::regex, std::function<void(const std::smatch &)>>> _instructions;

        std::array<ResourceData, 7> _resources;

        std::string _buffer;

        std::shared_ptr<Renderer::Renderer> _renderer;

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
         * @param m Must contain : x (int), y (int)
         */
        void _msz(const std::smatch &m);
        /**
         * @brief Display the content of a tile
         * @param m Must contain : x (int), y (int), q0 (int), q1 (int), q2 (int), q3 (int), q4 (int), q5 (int), q6 (int)
         */
        void _bct(const std::smatch &m);
        /**
         * @brief Display the name of the team
         * @param m Must contain : teamName (std::string)
         */
        void _tna(const std::smatch &m);
        /**
         * @brief Spawn a new player
         * @param m Must contain : playerId (int), x (int), y (int), orientation (Renderer::Compass), level (int), teamName (int)
         */
        void _pnw(const std::smatch &m);
        /**
         * @brief Set the position of a player
         * @param m Must contain : playerId (int), x (int), y (int), orientation (Renderer::Compass)
         */
        void _ppo(const std::smatch &m);
        /**
         * @brief Kicks a player from the server
         * @param m Must contain : playerId (int)
         */
        void _plv(const std::smatch &m);
        /**
         * @brief Display player's inventory
         * @param m Must contain : playerId (int), x (int), y (int), q0 (int), q1 (int), q2 (int), q3 (int), q4 (int), q5 (int), q6 (int)
         */
        void _pin(const std::smatch &m);
        /**
         * @brief Explusion
         * @param m Must contain : playerId (int)
         */
        void _pex(const std::smatch &m);
        /**
         * @brief Broadcast
         * @param m Must contain : playerId (int), message (std::string)
         */
        void _pbc(const std::smatch &m);
        /**
         * @brief Starts an incantation (by the first player)
         * @param m Must contain : x (int), y (int), level (int), playersId... (multiple int)
         */
        void _pic(const std::smatch &m);
        /**
         * @brief Stops an incantation
         * @param m Must contain : x (in), y (int), result (std::string)
         */
        void _pie(const std::smatch &m);
        /**
         * @brief Egg laying by the player
         * @param m Must contain : playerId (int)
         */
        void _pfk(const std::smatch &m);
        /**
         * @brief Drops resources
         * @param m Must contain : playerId (int), resourceNumber (int)
         */
        void _pdr(const std::smatch &m);
        /**
         * @brief Takes resources
         * @param m Must contain : playerId (int), resourceNumber (int)
         */
        void _pgt(const std::smatch &m);
        /**
         * @brief Despawn a player (death)
         * @param m Must contain : playerId (int)
         */
        void _pdi(const std::smatch &m);
        /**
         * @brief Lay an egg by a player
         * @param m Must contain : eggId (int), playerId (int), x (int), y (int)
         */
        void _enw(const std::smatch &m);
        /**
         * @brief Player connection for an egg
         * @param m Must contain : eggId (int)
         */
        void _ebo(const std::smatch &m);
        /**
         * @brief Despawn an egg (death)
         * @param m Must contain : eggId (int)
         */
        void _edi(const std::smatch &m);
        /**
         * @brief Time unit request
         * @param m Must contain : timeUnit (int)
         */
        void _sgt(const std::smatch &m);
        /**
         * @brief Time unit modification
         * @param m Must contain : timeUnit (int)
         */
        void _sst(const std::smatch &m);
        /**
         * @brief Ends the game
         * @param m Must contain : teamName (std::string)
         */
        void _seg(const std::smatch &m);
        /**
         * @brief Message from the server
         * @param m Must contain : teamName (std::string)
         */
        void _smg(const std::smatch &m);
        /**
         * @brief Unknown command
         * @param m Must not contain anything
         */
        void _suc(const std::smatch &m);
        /**
         * @brief Command parameter
         */
        void _sbp() {}
};
