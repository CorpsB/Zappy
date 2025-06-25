/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** AI
*/

#pragma once

#define FOOD_THRESHOLD 8.0
#define ACTION_DELAY_MS 50

#include <string>
#include <memory>
#include <vector>
#include "persona/Persona.hpp"
#include "../parser/parser.hpp"
#include "../utils/utils.hpp"
#include "../network/Socket.hpp"
#include "inventory/Inventory.hpp"
#include "sound/SoundSystem.hpp"

namespace ai::entity
{
    enum Goal {
        FOOD,
        STONE,
        MEETUP,
        MEETUP_POINT,
        ELEVATION_MASTER,
        ELEVATION_SLAVE
    };

    struct ElevationRecipe {
        int player;
        int linemate;
        int deraumere;
        int sibur;
        int mendiane;
        int phiras;
        int thystame;
    };

    struct SpiralState {
        int leg_max_steps = 1;
        int leg_steps_taken = 0;
        int legs_completed_at_current_length = 0;
    };

    class AI {
        public:
            AI(int id);
            ~AI() = default;

            void start(const ai::parser::Config &config);
            void run(const ai::parser::Config &config);
            std::string doAction(const std::string &action);
            bool doKoAction(const std::string &action);
            bool useBroadcast(const std::string &message);
            void stop();

            // helper
            int countPlayersOnTile(int idx, const std::string &look);
            int findItemInLook(const std::string &look, const std::string &item);
            bool collectItem(const std::string &look, const std::string &name, int recipe_qty);
            bool collectAllItems(const std::string &look);

            // goal
            Goal getGoal(const std::string &look);
            bool hasEnoughRocks();
            std::string getRarestMissingStone();
            bool handleGoal(std::string &look, const std::string &goal);

            // moves
            std::string getDirectionName(Direction dir);
            std::vector<Direction> getMovesToTileLevel1Vision(int idx);
            std::vector<Direction> getMovesTowardsSoundDirection(Direction dir);
            bool executeMoves(std::string &look, const std::vector<Direction> &moves);
            bool executeSpiralMove(SpiralState &state);

            // action
            bool performWanderAction();
            bool performActionForGoal(std::string &look);

            // elevate
            bool setStoneForIncantation(const std::string &name, int qty,
                std::vector<std::string> &stones_to_set);
            bool setStonesForIncantation();
            bool incantate(const std::string &response);

        private:
            static const ElevationRecipe RECIPES[7];

            unsigned _id;
            unsigned _level;
            unsigned _food_level;
            Goal _goal;
            Persona _persona;
            Inventory _inventory;
            SoundSystem _sound_system;
            SpiralState _spiral_state;

            std::string _thread_name;
            network::Socket _socket;
    };
}
