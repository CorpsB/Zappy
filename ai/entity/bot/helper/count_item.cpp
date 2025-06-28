/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** count_player
*/

#include "../../AI.hpp"
#include "../../../utils/utils.hpp"
#include <algorithm>
#include <sstream>
#include <iterator>

int ai::entity::AI::countItemInLook(const std::string &look, const std::string &item)
{
    ai::utils::debug::Logger &logger = ai::utils::debug::Logger::GetInstance();

    if (look.empty() || look.front() != '[' || look.back() != ']') {
        logger.log("[Error] Bad Look string for item count: '" + look + "'");
        return -1;
    }

    try {
        std::string inner = look.substr(1, look.size() - 2);
        std::istringstream iss(inner);

        return std::count(std::istream_iterator<std::string>(iss),
            std::istream_iterator<std::string>(), item);
    } catch (const std::exception &e) {
        logger.log("[Error] Failed counting item '" + item + "' in look string '" + look + "': " + e.what());
        return -1;
    }
}

int ai::entity::AI::countItemOnTile(int idx, const std::string &look, const std::string &item)
{
    ai::utils::debug::Logger &logger = ai::utils::debug::Logger::GetInstance();

    if (look.empty() || look.front() != '[' || look.back() != ']') {
        logger.log("[Error] Bad Look string for " + item + " count: '" + look + "'");
        return -1;
    }

    try {
        std::string inner = look.substr(1, look.size() - 2);
        std::vector<std::string> tiles = ai::utils::string::split(inner, ',');

        if (idx < 0 || idx >= static_cast<int>(tiles.size())) {
            logger.log("[Warn] Tile index " + std::to_string(idx) + " out of bounds for look string.");
            return 0;
        }
        std::vector<std::string> contents = ai::utils::string::split(tiles[idx], ' ');
        return std::count(contents.begin(), contents.end(), item);
    } catch (const std::exception &e) {
        logger.log("[Error] Failed counting " + item + "s in look string '" + look + "': " + e.what());
        return -1;
    }
}
