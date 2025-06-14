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
    enum SoundDirection {
        NONE = -1,
        UP_LEFT,
        UP,
        UP_RIGHT,
        LEFT,
        RIGHT,
        DOWN_LEFT,
        DOWN,
        DOWN_RIGHT
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
            void setPlayerOrientation(SoundDirection orientation);
            SoundDirection getAjustedDirection(SoundDirection raw);
            SoundDirection getRawDirection(SoundDirection adjusted);
            SoundCell &getDirectionSound(SoundDirection direction);
            SoundDirection getNearestSoundDirection();
            SoundDirection setSound(const std::string &sound_str);

        private:
            SoundDirection _player;
            SoundCell _cells[8];
    };
}
