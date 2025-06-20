/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** count_player
*/

#include "../../AI.hpp"
#include "../../../utils/utils.hpp"
#include <algorithm>

int ai::entity::AI::countPlayersOnTile(int idx, const std::string &look)
{
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();

    if (look.empty() || look.front() != '[' || look.back() != ']') {
        logger.log("[Error] Bad look format.");
        return -1;
    }

    const std::string content = look.substr(1, look.size() - 2);
    const std::vector<std::string> tiles = utils::string::split(content, ',');

    if (idx >= 0 && idx < static_cast<int>(tiles.size())) {
        const std::string tile = tiles[idx];
        const std::vector<std::string> words = utils::string::split(tile, ' ');
        return std::count(words.begin(), words.end(), "player");
    }
    logger.log("Tile index " + std::to_string(idx) + " out of bounds for look string.");
    return 0;
}
