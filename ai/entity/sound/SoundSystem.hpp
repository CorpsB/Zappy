/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** SoundSystem
*/

#pragma once

#define MAX_SOUND_DURATION 2000

#include <chrono>
#include <string>

namespace ai::entity
{
    enum Direction {
        NONE = -1,
        HERE,
        UP,
        UP_LEFT,
        LEFT,
        DOWN_LEFT,
        DOWN,
        DOWN_RIGHT,
        RIGHT,
        UP_RIGHT,
    };

    struct SoundCell {
        int64_t delta;
        std::chrono::_V2::system_clock::time_point received_at;
        std::string message;
        int id;
    };

    class SoundSystem {
        public:
            SoundSystem();
            ~SoundSystem() = default;

            void update();
            void setPlayerOrientation(Direction orientation);
            Direction getAjustedDirection(Direction raw);
            Direction getRawDirection(Direction adjusted);
            SoundCell &getDirectionSound(Direction direction);
            Direction getNearestSoundDirection();
            Direction setSound(const std::string &sound_str);

        private:
            Direction _player;
            SoundCell _cells[8];
    };
}
