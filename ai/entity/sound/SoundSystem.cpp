/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** SoundSystem
*/

#include "SoundSystem.hpp"
#include "../../utils/utils.hpp"
#include <regex>

ai::entity::SoundSystem::SoundSystem()
{
    _player = UP;
    for (int i = 0; i < 9; ++i)
        _cells[i].clear();
}

void ai::entity::SoundSystem::update()
{
    const auto now = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 9; ++i) {
        auto &vec = _cells[i];
        vec.erase(std::remove_if(vec.begin(), vec.end(), [&](const SoundCell &cell) {
            const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - cell.received_at);
            return duration.count() > MAX_SOUND_DURATION;
        }), vec.end());
    }
}

void ai::entity::SoundSystem::clearIdMemory(int id)
{
    for (auto &vec : _cells) {
        vec.erase(std::remove_if(vec.begin(), vec.end(), [&](const SoundCell &cell) {
            return cell.id == id;
        }), vec.end());
    }
}

void ai::entity::SoundSystem::setPlayerOrientation(Direction orientation)
{
    _player = orientation;
}

ai::entity::Direction ai::entity::SoundSystem::getAjustedDirection(Direction raw)
{
    if (raw == HERE)
        return HERE;
    return static_cast<Direction>(((raw - _player + 8) % 8) + 1);
}

ai::entity::Direction ai::entity::SoundSystem::getRawDirection(Direction adjusted)
{
    if (adjusted == HERE)
        return HERE;
    return static_cast<Direction>(((adjusted - 1 + _player - 1) % 8) + 1);
}

ai::entity::SoundCell &ai::entity::SoundSystem::getDirectionSound(Direction ajusted)
{
    if (_cells[ajusted].empty())
        throw std::runtime_error("No SoundCell available in this direction.");

    auto &vec = _cells[ajusted];
    auto minId = std::min_element(vec.begin(), vec.end(), [](const SoundCell &a, const SoundCell &b) {
        return a.id < b.id;
    });

    return *minId;
}

ai::entity::Direction ai::entity::SoundSystem::getNearestSoundDirection(const std::string &target)
{
    int bestId = std::numeric_limits<int>::max();
    Direction bestDir = NONE;

    for (int i = 0; i < 9; ++i) {
        for (const auto &cell : _cells[i]) {
            if (cell.message == target && cell.id < bestId) {
                bestId = cell.id;
                bestDir = getRawDirection(static_cast<Direction>(i));
            }
        }
    }
    return bestDir;
}

// message [direction], [id]|[timestamp]|[message]
ai::entity::Direction ai::entity::SoundSystem::setSound(const std::string &sound_str)
{
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
    std::regex pattern(R"(message\s*(\d+),\s*(\d+)\|(.+))");
    std::smatch match;

    if (!std::regex_match(sound_str, match, pattern)) {
        logger.log("[Error] Invalid sound format: regex mismatch '" + sound_str + "'.");
        return NONE;
    }

    int direction = std::stoi(match[1].str());
    const int id = std::stoi(match[2].str());
    const std::string message = match[3].str();

    if (direction < 0 || direction > 8) {
        logger.log("[Error] Invalid direction index: must be between 0 and 8");
        return NONE;
    }

    clearIdMemory(id);
    direction = getAjustedDirection(static_cast<Direction>(direction));
    _cells[direction].push_back(SoundCell{
        std::chrono::high_resolution_clock::now(),
        message,
        id
    });
    return static_cast<Direction>(direction);
}
