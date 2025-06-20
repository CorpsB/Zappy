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
    for (int i = 0; i < 8; ++i) {
        _cells[i].id = -1;
        _cells[i].message = "";
    }
}

void ai::entity::SoundSystem::update()
{
    const auto actual = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 8; ++i) {
        if (_cells[i].id == -1)
            continue;

        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(actual - _cells[i].received_at);

        if (duration.count() > MAX_SOUND_DURATION) {
            _cells[i].id = -1;
            _cells[i].message = "";
        }
    }
}

void ai::entity::SoundSystem::setPlayerOrientation(SoundDirection orientation)
{
    _player = orientation;
}

ai::entity::SoundDirection ai::entity::SoundSystem::getAjustedDirection(SoundDirection raw)
{
    return static_cast<SoundDirection>((raw - _player + 9) % 8);
}

ai::entity::SoundDirection ai::entity::SoundSystem::getRawDirection(SoundDirection adjusted)
{
    return static_cast<SoundDirection>((adjusted + _player - 1 + 8) % 8);
}

ai::entity::SoundCell &ai::entity::SoundSystem::getDirectionSound(SoundDirection ajusted)
{
    return _cells[ajusted];
}

ai::entity::SoundDirection ai::entity::SoundSystem::getNearestSoundDirection()
{
    SoundDirection dir = NONE;
    int64_t min_duration = MAX_SOUND_DURATION;

    for (int i = 0; i < 8; ++i) {
        if (_cells[i].id == -1)
            continue;
        if (_cells[i].delta < min_duration) {
            min_duration = _cells[i].delta;
            dir = static_cast<SoundDirection>(i);
        }
    }
    if (dir != NONE)
        return getRawDirection(dir);
    return dir;
}

// message [direction], [id]|[timestamp]|[message]
ai::entity::SoundDirection ai::entity::SoundSystem::setSound(const std::string &sound_str)
{
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
    std::regex pattern(R"(message\s*\[(\d+)\],\s*(\d+)\|(\d+)\|(.+))");
    std::smatch match;

    if (!std::regex_match(sound_str, match, pattern)) {
        logger.log("[Error] Invalid sound format: regex mismatch");
        return NONE;
    }

    int direction = std::stoi(match[1].str());
    const int id = std::stoi(match[2].str());
    const std::string message = match[4].str();
    int64_t sended_at_64;

    try {
        sended_at_64 = std::stoll(match[3].str());
    } catch (...) {
        logger.log("[Error] Invalid timestamp: must be a valid int64");
        return NONE;
    }

    if (direction < 0 || direction > 7) {
        logger.log("[Error] Invalid direction index: must be between 0 and 7");
        return NONE;
    }

    const auto date_now = std::chrono::high_resolution_clock::now();
    const auto sended_at = std::chrono::high_resolution_clock::time_point{
        std::chrono::milliseconds{sended_at_64}
    };

    if (sended_at > date_now) {
        logger.log("[Error] Invalid timestamp: message from the future");
        return NONE;
    }

    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(date_now - sended_at);

    direction = getAjustedDirection(static_cast<SoundDirection>(direction));
    _cells[direction].id = id;
    _cells[direction].message = message;
    _cells[direction].received_at = date_now;
    _cells[direction].delta = duration.count();
    return static_cast<SoundDirection>(direction);
}
