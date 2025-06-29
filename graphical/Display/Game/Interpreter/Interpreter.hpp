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
        /**
         * @brief Constructs the Interpreter object with a shared renderer.
         *
         * Initializes the instruction dispatch table (`_instructions`) with regex patterns
         * and their corresponding handler functions. Also sets up resource definitions.
         *
         * @param renderer Shared pointer to the 3D renderer used for updating the scene.
         */
        Interpreter(std::shared_ptr<Renderer::Renderer> renderer, std::shared_ptr<Renderer::EntityClass> entity);
        ~Interpreter() = default;

        /**
         * @brief Interprets and dispatches server commands from a raw input string.
         *
         * Parses the buffer line by line, matches each line against known regex instructions,
         * and invokes the corresponding handler. Unrecognized or incomplete data is preserved
         * in the buffer for later reprocessing.
         *
         * @param data A string containing raw server commands (may contain multiple lines).
         */
        void interpret(const std::string &data);
    private:
        std::unordered_map<std::string, std::pair<std::regex, std::function<void(const std::smatch &)>>> _instructions;

        std::array<ResourceData, 7> _resources;

        std::string _buffer;

        std::shared_ptr<Renderer::Renderer> _renderer;
        std::shared_ptr<Renderer::EntityClass> _entity;

        std::unordered_map<std::string, sf::Color> _teamColor;

        /**
         * @brief Checks if the given color is sufficiently different from existing team colors.
         *
         * Uses Euclidean RGB distance to ensure distinctiveness.
         *
         * @param newColor The new team color to evaluate.
         * @return true if the color is sufficiently different, false otherwise.
         */
        bool _bigEnoughDiffColor(sf::Color newColor);

        /**
         * @brief Handles the `msz` command to set the map size.
         *
         * Spawns ground tiles and initializes the renderer's map dimensions.
         *
         * @param m Match object containing x and y map size.
         */
        void _msz(const std::smatch &m);
        /**
         * @brief Handles the `bct` command to update tile resources.
         *
         * Updates the resource quantities on a given tile and spawns or removes
         * resource models in the scene accordingly.
         *
         * @param m Match object containing tile coordinates and quantities for 7 resource types.
         */
        void _bct(const std::smatch &m);
        /**
         * @brief Display the name of the team
         * @param m Must contain : teamName (std::string)
         */
        void _tna(const std::smatch &m);
        /**
         * @brief Handles the `pnw` command to spawn a new player.
         *
         * Spawns a body and eyes model for the player with the appropriate team color,
         * position, orientation, and level.
         *
         * @param m Match object containing player ID, position, orientation, level, and team name.
         */
        void _pnw(const std::smatch &m);
        /**
         * @brief Handles the `ppo` command to update a player's position and orientation.
         *
         * Updates position and schedules movement and rotation animations if necessary.
         * Performs recalibration if the reported position doesn't match expectations.
         *
         * @param m Match object containing player ID, position, and orientation.
         */
        void _ppo(const std::smatch &m);
        /**
         * @brief Handles the `plv` command to update a player's level.
         *
         * Removes the old eyes model and spawns a new one matching the updated level.
         *
         * @param m Match object containing player ID and new level.
         */
        void _plv(const std::smatch &m);
        /**
         * @brief Handles the `pin` command to update a player's inventory.
         *
         * Sets the inventory for the matching player entity.
         *
         * @param m Match object containing player ID and quantities of all resources.
         */
        void _pin(const std::smatch &m);
        /**
         * @brief Handles the `pex` command to trigger an expulsion effect.
         *
         * Spawns a temporary visual effect at the player's position to indicate expulsion.
         *
         * @param m Match object containing the player ID.
         */
        void _pex(const std::smatch &m);
        /**
         * @brief Handles the `pbc` command to display a broadcast message.
         *
         * Logs the message in the interface with the player's team color.
         *
         * @param m Match object containing player ID and the broadcast message.
         */
        void _pbc(const std::smatch &m);
        /**
         * @brief Handles the `pic` command to indicate the start of an incantation.
         *
         * Spawns an incantation ring and logs the event for the first player involved.
         *
         * @param m Match object containing tile position and list of player IDs.
         */
        void _pic(const std::smatch &m);
        /**
         * @brief Handles the `pie` command to end an incantation.
         *
         * Removes the incantation ring from the tile and logs the outcome.
         *
         * @param m Match object containing tile coordinates and the result status.
         */
        void _pie(const std::smatch &m);
        /**
         * @brief Handles the `pfk` command to indicate a player has laid an egg.
         *
         * Logs the event in the instruction history.
         *
         * @param m Match object containing the player ID.
         */
        void _pfk(const std::smatch &m);
        /**
         * @brief Handles the `pdr` command for dropping a resource.
         *
         * Logs the action in the instruction history.
         *
         * @param m Match object containing player ID and resource number.
         */
        void _pdr(const std::smatch &m);
        /**
         * @brief Handles the `pgt` command for picking up a resource.
         *
         * Logs the action in the instruction history.
         *
         * @param m Match object containing player ID and resource number.
         */
        void _pgt(const std::smatch &m);
        /**
         * @brief Handles the `pdi` command to remove a player (death).
         *
         * Removes all parts associated with the player and related incantation rings.
         *
         * @param m Match object containing the player ID.
         */
        void _pdi(const std::smatch &m);
        /**
         * @brief Handles the `enw` command to spawn an egg.
         *
         * Places the egg entity at a slightly offset position from the player.
         *
         * @param m Match object containing egg ID, parent player ID, and coordinates.
         */
        void _enw(const std::smatch &m);
        /**
         * @brief Handles the `ebo` command when an egg hatches.
         *
         * Removes the egg from the scene and logs the event.
         *
         * @param m Match object containing the egg ID.
         */
        void _ebo(const std::smatch &m);
        /**
         * @brief Handles the `edi` command when an egg dies.
         *
         * Removes the egg from the scene and logs the event.
         *
         * @param m Match object containing the egg ID.
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
