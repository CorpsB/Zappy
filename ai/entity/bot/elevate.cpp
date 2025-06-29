/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** elevate
*/

/**
 * @file elevate.cpp
 * @brief Implementation of stone management methods for incantations.  
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @see AI.hpp
 */

#include "../AI.hpp"
#include <thread>

bool ai::entity::AI::setStoneForIncantation(const std::string &name, int qty,
    std::vector<std::string> &stones_to_set)
{
    if (qty == 0)
        return true;
    if (_inventory.getItem(name) < qty) {
        utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
        logger.log("Not enough " + name + " to elevate.");
        return false;
    }
    for (int i = 0; i < qty; ++i)
        stones_to_set.push_back(name);
    return true;
}

bool ai::entity::AI::setStonesForIncantation()
{
    ai::utils::debug::Logger &logger = ai::utils::debug::Logger::GetInstance();
    std::vector<std::string> stones_to_set;

    if (!(setStoneForIncantation("linemate", RECIPES[_level - 1].linemate, stones_to_set) &&
    setStoneForIncantation("deraumere", RECIPES[_level - 1].deraumere, stones_to_set) &&
    setStoneForIncantation("sibur", RECIPES[_level - 1].sibur, stones_to_set) &&
    setStoneForIncantation("mendiane", RECIPES[_level - 1].mendiane, stones_to_set) &&
    setStoneForIncantation("phiras", RECIPES[_level - 1].phiras, stones_to_set) &&
    setStoneForIncantation("thystame", RECIPES[_level - 1].thystame, stones_to_set)))
        return false;

    for (const std::string &stone : stones_to_set) {
        if (!doKoAction("Set " + stone)) {
            logger.log("Failed to set " + stone + " during L" + std::to_string(_level + 1) + " prep.");
            return false;
        }
    }
    return true;
}

bool ai::entity::AI::incantate(const std::string &response)
{
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();

    logger.log("I take part in the incantation for level " + std::to_string(_level + 1) + ".");
    if (response == "dead")
        return false;
    if (response.find("Elevation underway") != std::string::npos) {
        const std::string final_response = doAction("");
        if (final_response == "dead")
            return false;
        if (final_response == "ko")
            logger.log("L" + std::to_string(_level + 1) + " Elevation failed.");
        else if (final_response.find("Current level: " + std::to_string(_level + 1)) != std::string::npos) {
            ++_level;
            logger.log("L" + std::to_string(_level) + " Elevation success! Now Level " + std::to_string(_level) + ".");
        } else {
            logger.log("L" + std::to_string(_level + 1) + " Elevation led to unexpected response: '" + final_response + "'.");
            return false;
        }
    } else {
        logger.log("L" + std::to_string(_level + 1) + " Incantation start failed: '" + response + "'.");
    }
    return true;
}
