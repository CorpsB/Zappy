/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** AI
*/

/**
 * @file AI.hpp
 * @brief Declaration of the AI class orchestrating Zappy bot behavior.  
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @details
 * Manages server connection, sending and receiving commands,
 * goal determination logic, resource collection, movement,
 * and incantation to level up the bot.
 */

#pragma once

#define MAX_FOOD_THRESHOLD 20.0  // maximum food threshold before overload
#define HIGH_FOOD_THRESHOLD 16.0 // high food threshold to prioritize resources
#define LOW_FOOD_THRESHOLD 6.0   // low food threshold to return to gathering food

#define REPRODUCE_THRESHOLD 10   // maximum number of bots to reproduce simultaneously
#define ACTION_DELAY_MS 50       // delay between actions in wait mode (ms)

#include <string>
#include <vector>
#include "persona/Persona.hpp"
#include "../parser/parser.hpp"
#include "../utils/utils.hpp"
#include "../network/Socket.hpp"
#include "inventory/Inventory.hpp"
#include "sound/SoundSystem.hpp"

namespace ai::entity
{
    /**
     * @enum Goal
     * @brief Types of goals pursued by the AI.
     */
    enum Goal {
        FOOD,               // gather food
        STONE,              // collect stones for incantation
        MEETUP,             // join a meetup point
        MEETUP_POINT,       // send a meetup point signal
        ELEVATION_MASTER,   // start incantation (leader)
        ELEVATION_SLAVE,    // participate in incantation (slave)
        REPRODUCE           // reproduce by laying an egg
    };

    /**
     * @struct ElevationRecipe
     * @brief Player and resource amounts required per elevation level.
     */
    struct ElevationRecipe {
        int player;     // number of players required
        int linemate;   // amount of linemate
        int deraumere;  // amount of deraumere
        int sibur;      // amount of sibur
        int mendiane;   // amount of mendiane
        int phiras;     // amount of phiras
        int thystame;   // amount of thystame
    };

    /**
     * @struct SpiralState
     * @brief State for spiral search around the bot.
     */
    struct SpiralState {
        int leg_max_steps = 1; // maximum steps per spiral leg
        int leg_steps_taken = 0; // steps taken in current leg
        int legs_completed_at_current_length = 0; // legs completed at current length
    };

    /**
     * @class AI
     * @brief Main class managing bot behavior and actions.
     *
     * @details
     * Handles socket setup, main listen/action loop,
     * goal selection, movement, resource collection,
     * and incantation for leveling up.
     */
    class AI {
        public:
            /**
             * @brief Constructs an AI bot with a unique identifier.
             * @param id Numeric identifier of the bot.
             */
            AI(int id);

            /**
             * @brief Default destructor.
             */
            ~AI() = default;

            /**
             * @brief Initializes the logger and performs server handshake.
             * @param config Configuration parameters (port, name, host, etc.).
             */
            void start(const ai::parser::Config &config);

            /**
             * @brief Main loop: updates state and executes actions.
             * @param config Configuration parameters.
             */
            void run(const ai::parser::Config &config);

            /**
             * @brief Sends a command and reads a single-line response.
             * @param action Command to send (without newline).
             * @return Server response or "dead" on error.
             */
            std::string doAction(const std::string &action);

            /**
             * @brief Sends a command and handles "ko" with random moves.
             * @param action Command to send (without newline).
             * @return false if "dead", true otherwise.
             */
            bool doKoAction(const std::string &action);

            /**
             * @brief Broadcasts a message to other bots.
             * @param message Message to broadcast.
             * @return true if send succeeds, false otherwise.
             */
            bool useBroadcast(const std::string &message);

            /**
             * @brief Ends the session, logs final state, and flushes logs.
             */
            void stop();

            /**
             * @brief Counts occurrences of an item in the Look string.
             * @param look String from Look command.
             * @param item Name of the item to count.
             * @return Number of occurrences or -1 on format error.
             */
            int countItemInLook(const std::string &look, const std::string &item);

            /**
             * @brief Counts occurrences of an item on a specific tile.
             * @param idx   Tile index in vision.
             * @param look  String from Look command.
             * @param item  Item name.
             * @return Number of occurrences or -1 on error.
             */
            int countItemOnTile(int idx, const std::string &look, const std::string &item);

            /**
             * @brief Finds the first tile index containing an item in Look.
             * @param look String from Look command.
             * @param item Item to find.
             * @return Tile index, -2 if not found, -1 on error.
             */
            int findItemInLook(const std::string &look, const std::string &item);

            /**
             * @brief Calculates vision range depth for a tile index.
             * @param idx Tile index in vision.
             * @return Range depth of the tile.
             */
            int determineLookDistance(int idx);

            /**
             * @brief Determines whether to pick up or skip an item on current tile.
             * @param look       String from Look command.
             * @param name       Item name.
             * @param recipe_qty Quantity required by the recipe.
             * @param is_players True if a player is present.
             * @return true if skip or pick-up succeeds, false otherwise.
             */
            bool collectItem(const std::string &look, const std::string &name,
                int recipe_qty, bool is_players);

            /**
             * @brief Attempts to pick up all necessary items on current tile.
             * @param look String from Look command.
             * @return true if all pickups succeed, false otherwise.
             */
            bool collectAllItems(const std::string &look);

            /**
             * @brief Determines the next goal based on state and vision.
             * @param look String from Look command.
             * @return Selected goal.
             */
            Goal getGoal(const std::string &look);

            /**
             * @brief Checks if bot has enough stones for incantation.
             * @return true if sufficient, false otherwise.
             */
            bool hasEnoughRocks();

            /**
             * @brief Returns the name of the rarest missing stone.
             * @return Name of the most critical missing resource.
             */
            std::string getRarestMissingStone();

            /**
             * @brief Executes collection or incantation logic for a goal.
             * @param look String from Look command, updated during movement.
             * @param goal Name of the goal to handle.
             * @return true if action completes positively, false otherwise.
             */
            bool handleGoal(std::string &look, const std::string &goal);

            /**
             * @brief Returns the command string corresponding to a direction.
             * @param dir Direction to translate.
             * @return Command ("Forward", "Left", "Right").
             */
            std::string getDirectionName(Direction dir);

            /**
             * @brief Generates movement sequence to reach a vision tile.
             * @param idx Tile index in vision.
             * @return List of directions to execute.
             */
            std::vector<Direction> getMovesToTileLevelVision(int idx);

            /**
             * @brief Generates movement sequence toward a sound direction.
             * @param dir Adjusted sound direction.
             * @return List of directions to execute.
             */
            std::vector<Direction> getMovesTowardsSoundDirection(Direction dir);

            /**
             * @brief Executes a sequence of moves, updating vision after each.
             * @param look  String from Look command, updated internally.
             * @param moves List of directions to execute.
             * @return true if all moves succeed, false otherwise.
             */
            bool executeMoves(std::string &look, const std::vector<Direction> &moves);

            /**
             * @brief Performs a spiral movement to explore surroundings.
             * @param state Reference to spiral state.
             * @return true if action succeeds, false if "dead".
             */
            bool executeSpiralMove(SpiralState &state);

            /**
             * @brief Performs a random wander action (left or forward).
             * @return true if command does not return "dead".
             */
            bool performWanderAction();

            /**
             * @brief Chooses and executes action based on current goal.
             * @param look String from Look command.
             * @return true if action succeeds, false otherwise.
             */
            bool performActionForGoal(std::string &look);

            /**
             * @brief Fills stones_to_set vector for a given stone.
             * @param name          Stone name.
             * @param qty           Quantity required.
             * @param stones_to_set Reference to vector to fill.
             * @return true if qty is zero or available, false otherwise.
             */
            bool setStoneForIncantation(const std::string &name, int qty,
                std::vector<std::string> &stones_to_set);

            /**
             * @brief Places all stones required for incantation.
             * @return true if all stones set, false otherwise.
             */
            bool setStonesForIncantation();

            /**
             * @brief Begins incantation and processes response for elevation.
             * @param response Initial response after "Incantation" command.
             * @return true if incantation completes successfully, false otherwise.
             */
            bool incantate(const std::string &response);

        private:
            static const ElevationRecipe RECIPES[7]; // elevation recipes per level

            unsigned        _id;             // bot identifier
            unsigned        _level;          // current level
            unsigned        _food_level;     // remaining food
            Goal            _goal;           // current goal
            Persona         _persona;        // personality traits
            Inventory       _inventory;      // inventory manager
            SoundSystem     _sound_system;   // sound system
            SpiralState     _spiral_state;   // spiral search state
            bool            _dock_mode;      // incantation preparation mode
            int             _free_slots;     // free slots for reproduction
            std::string     _thread_name;    // log prefix
            network::Socket _socket;         // communication socket
    };
}
