/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** SoundSystem
*/

#pragma once

#define MAX_SOUND_DURATION 6000
#define DISTANCE_MULTIPLE 1.3

#include <chrono>
#include <string>
#include <vector>

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
            void clearIdMemory(int id);
            Direction getAjustedDirection(Direction raw);
            Direction getRawDirection(Direction adjusted);
            SoundCell &getDirectionSound(Direction direction);
            Direction getNearestSoundDirection(const std::string &target);
            Direction setSound(const std::string &sound_str);

        private:
            Direction _player;
            std::vector<SoundCell> _cells[9];
    };
}
