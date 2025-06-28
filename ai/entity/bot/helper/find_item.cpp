/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** find_item
*/

#include "../../AI.hpp"
#include "../../../utils/utils.hpp"
#include <algorithm>

int ai::entity::AI::determineLookDistance(int idx)
{
    int i = 0;
    int lvl = 0;

    while (i + (2 * lvl + 1) <= idx) {
        i += (2 * lvl + 1);
        ++lvl;
    }
    return lvl;
}

int ai::entity::AI::findItemInLook(const std::string &look, const std::string &item)
{
    ai::utils::debug::Logger &logger = ai::utils::debug::Logger::GetInstance();

    if (look.empty() || look.front() != '[' || look.back() != ']') {
        logger.log("[Error] Bad Look string format: '" + look + "'");
        return -1;
    }

    try {
        std::string inner = look.substr(1, look.size() - 2);
        std::vector<std::string> tiles = ai::utils::string::split(inner, ',');

        for (int i = 0; i < static_cast<int>(tiles.size()); ++i) {
            std::vector<std::string> contents = ai::utils::string::split(tiles[i], ' ');
            if (std::find(contents.begin(), contents.end(), item) != contents.end())
                return i;
        }
        return -2;
    } catch (const std::exception &e) {
        logger.log("[Error] Failed parsing Look string '" + look + "': " + e.what());
        return -1;
    }
}
