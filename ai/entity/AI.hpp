/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** AI
*/

#pragma once

#define FOOD_THRESHOLD 8.0

#include <string>
#include <memory>
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
        ELEVATION
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

    class AI {
        public:
            AI(int id);
            ~AI() = default;

            void start(const ai::parser::Config &config);
            void run(const ai::parser::Config &config);
            std::string doAction(const std::string &action);
            void stop();

            // helper
            int countPlayersOnTile(int idx, const std::string &look);

            // goal
            Goal getGoal(const std::string &look);
            bool hasEnoughRocks();
            std::string getRarestMissingStone();

        private:
            static const ElevationRecipe RECIPES[7];

            unsigned _id;
            unsigned _level;
            unsigned _food_level;
            Goal _goal;
            Persona _persona;
            Inventory _inventory;
            SoundSystem _sound_system;

            std::string _thread_name;
            utils::debug::Logger _logger;
            network::Socket _socket;
    };
}
