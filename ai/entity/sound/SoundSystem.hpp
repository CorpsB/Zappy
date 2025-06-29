/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** SoundSystem
*/

/**
 * @file SoundSystem.hpp
 * @brief Manages positional sound cues for AI entities based on direction and timing.  
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @details
 * Buffers incoming sound messages tagged with direction and ID, prunes expired sounds,
 * and computes adjusted directions relative to the player's orientation.
 */

#pragma once

#define MAX_SOUND_DURATION 6000
#define DISTANCE_MULTIPLE 1.3

#include <chrono>
#include <string>
#include <vector>

namespace ai::entity
{
    /**
     * @enum Direction
     * @brief Enumeration of possible sound directions relative to the listener.
     */
    enum Direction {
        NONE = -1, // no valid direction
        HERE, // sound on listener tile
        UP,
        UP_LEFT,
        LEFT,
        DOWN_LEFT,
        DOWN,
        DOWN_RIGHT,
        RIGHT,
        UP_RIGHT,
    };

    /**
     * @struct SoundCell
     * @brief Represents a single received sound event.  
     */
    struct SoundCell {
        std::chrono::_V2::system_clock::time_point received_at; // timestamp of receipt
        std::string message; // payload of the sound
        int id; // unique ID for source comparison
    };

    /**
     * @class SoundSystem
     * @brief Handles buffering and directional computation of sound events.  
     *
     * @details
     * Keeps nine vectors—one per direction—for recently received sounds,
     * prunes entries older than MAX_SOUND_DURATION, and provides methods
     * to interpret and retrieve nearest or orientation‑adjusted sounds.
     */
    class SoundSystem {
        public:
            /**
             * @brief Constructs the system, setting default orientation and clearing buffers.
             */
            SoundSystem();

            /**
             * @brief Virtual destructor.
             */
            ~SoundSystem() = default;

            /**
             * @brief Removes expired SoundCell entries from all direction buffers.
             */
            void update();

            /**
             * @brief Sets the listener’s current facing direction.
             * @param orientation New player orientation.
             */
            void setPlayerOrientation(Direction orientation);

            /**
             * @brief Clears any stored sounds from a specific source ID across all buffers.
             * @param id Source identifier to clear.
             */
            void clearIdMemory(int id);

            /**
             * @brief Converts a raw direction index into one adjusted by player orientation.
             * @param raw Raw Direction value received from server.
             * @return Orientation‑adjusted Direction.
             */
            Direction getAjustedDirection(Direction raw);

            /**
             * @brief Reverses an adjusted direction back to the raw index.
             * @param adjusted Orientation‑adjusted Direction.
             * @return Raw Direction index.
             */
            Direction getRawDirection(Direction adjusted);

            /**
             * @brief Retrieves the oldest SoundCell in the given adjusted direction.
             * @param direction Adjusted Direction index.
             * @return Reference to SoundCell with smallest ID.
             * @throws std::runtime_error if no sounds are available in that direction.
             */
            SoundCell &getDirectionSound(Direction direction);

            /**
             * @brief Finds the direction of the nearest sound matching a target message.
             * @param target Message to search for.
             * @return Raw Direction of the nearest matching SoundCell, or NONE.
             */
            Direction getNearestSoundDirection(const std::string &target);

            /**
             * @brief Counts messages matching the target at the listener’s location.
             * @param target Message to count.
             * @return Number of matching sounds in HERE direction.
             */
            int getNbMessage(const std::string &target);

            /**
             * @brief Parses and stores a sound string from the server.
             * @param sound_str Raw server string in format "message D,X|msg".
             * @return Adjusted Direction index where the sound is stored, or NONE on parse error.
             */
            Direction setSound(const std::string &sound_str);

        private:
            Direction _player;                // current facing direction
            std::vector<SoundCell> _cells[9]; // buffers for each raw direction
    };
}
