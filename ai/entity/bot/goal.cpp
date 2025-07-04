/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** goal
*/

/**
 * @file goal.cpp
 * @brief Implements goal determination helpers for AI decision logic.  
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @see AI.hpp
 */

#include "../AI.hpp"

const ai::entity::ElevationRecipe ai::entity::AI::RECIPES[7] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1},
};

bool ai::entity::AI::hasEnoughRocks()
{
    if (_inventory.getItem("linemate") >= RECIPES[_level - 1].linemate &&
    _inventory.getItem("deraumere") >= RECIPES[_level - 1].deraumere &&
    _inventory.getItem("sibur") >= RECIPES[_level - 1].sibur &&
    _inventory.getItem("mendiane") >= RECIPES[_level - 1].mendiane &&
    _inventory.getItem("phiras") >= RECIPES[_level - 1].phiras &&
    _inventory.getItem("thystame") >= RECIPES[_level - 1].thystame)
        return true;
    return false;
}

std::string ai::entity::AI::getRarestMissingStone()
{
    if (_inventory.getItem("thystame") < RECIPES[_level - 1].thystame)
        return "thystame";
    if (_inventory.getItem("phiras") < RECIPES[_level - 1].phiras)
        return "phiras";
    if (_inventory.getItem("mendiane") < RECIPES[_level - 1].mendiane)
        return "mendiane";
    if (_inventory.getItem("sibur") < RECIPES[_level - 1].sibur)
        return "sibur";
    if (_inventory.getItem("deraumere") < RECIPES[_level - 1].deraumere)
        return "deraumere";
    return "linemate";
}

ai::entity::Goal ai::entity::AI::getGoal(const std::string &look)
{
    if (!_dock_mode || _food_level < LOW_FOOD_THRESHOLD)
    {
        _dock_mode = false;

        if (_food_level < HIGH_FOOD_THRESHOLD)
            return FOOD;

        if (_level == 8)
            return STONE;

        if (_free_slots > 0)
            return REPRODUCE;
    }

    int nb_players = _sound_system.getNbMessage("READY_" + std::to_string(_level + 1)) + 1;
    const bool enough_rocks = hasEnoughRocks();
    const Direction meetup = _sound_system.getNearestSoundDirection("MEETUP_" + std::to_string(_level + 1));
    if (meetup != NONE) {
        SoundCell &cell = _sound_system.getDirectionSound(meetup);

        if (meetup == HERE)
            ++nb_players;
        if (_food_level >= HIGH_FOOD_THRESHOLD)
            _dock_mode = true;
        if (enough_rocks) {
            if (nb_players >= RECIPES[_level - 1].player)
                return (cell.id < _id) ? ELEVATION_SLAVE : ELEVATION_MASTER;
            if (cell.id < _id)
                return (meetup == HERE) ? ELEVATION_SLAVE : MEETUP;
            return MEETUP_POINT;
        }
        return (meetup == HERE) ? ELEVATION_SLAVE : MEETUP;
    } else if (enough_rocks) {
        if (_level == 1 || nb_players >= RECIPES[_level - 1].player)
            return ELEVATION_MASTER;
        return MEETUP_POINT;
    }
    return (_food_level < HIGH_FOOD_THRESHOLD) ? FOOD : STONE;
}

bool ai::entity::AI::handleGoal(std::string &look, const std::string &goal)
{
    ai::utils::debug::Logger &logger = ai::utils::debug::Logger::GetInstance();
    const int item_idx = findItemInLook(look, goal);

    if (item_idx == 0) {
        logger.log(utils::string::capitalize(goal) + " on current tile. Taking.");
        return doKoAction("Take " + goal);
    } else if (item_idx > 0) {
        const std::vector<Direction> moves = getMovesToTileLevelVision(item_idx);
        logger.log(utils::string::capitalize(goal) + " on tile " + std::to_string(item_idx) + ". Moving to take.");
        if (!executeMoves(look, moves))
            return false;
        return doKoAction("Take " + goal);
    } else if (item_idx == -2) {
        logger.log(utils::string::capitalize(goal) + " not seen. Executing spiral move.");
        return executeSpiralMove(_spiral_state);
    } else {
        logger.log("Halting " + goal + " goal due to look parse error.");
        return false;
    }
}
