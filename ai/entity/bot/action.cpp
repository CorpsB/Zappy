/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** action
*/

#include "../AI.hpp"
#include <chrono>
#include <thread>

bool ai::entity::AI::performWanderAction()
{
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
    std::string action;

    if (static_cast<float>(std::rand()) / RAND_MAX < 0.3f) {
        action = "Left";
    } else {
        action = "Forward";
    }
    logger.log("Wandering: " + action + ".");
    return doAction(action) != "dead";
}

bool ai::entity::AI::performActionForGoal(std::string &look)
{
    utils::debug::Logger &logger = ai::utils::debug::Logger::GetInstance();

    switch (_goal) {
        case FOOD:
            return handleGoal(look, "food");

        case STONE: {
            const std::string rarest_missing = getRarestMissingStone();
            if (determineLookDistance(findItemInLook(look, "food")) <
            determineLookDistance(findItemInLook(look, rarest_missing))) {
                logger.log("I make a detour to look for food");
                return handleGoal(look, "food");
            }
            return handleGoal(look, rarest_missing);
        }

        case ELEVATION_MASTER: {
            _dock_mode = true;

            logger.log("Attempting L" + std::to_string(_level + 1) + " Incantation.");
            if (!setStonesForIncantation()) {
                logger.log("L" + std::to_string(_level + 1) + " stone setting phase failed.");
                return false;
            }

            logger.log("Sending everyone incantation signal for level " + std::to_string(_level + 1));
            if (_level == 1) {
                if (!_socket.sendCommand("Incantation"))
                    return false;
                return incantate(doAction(""));
            } else {
                if (!useBroadcast("INCANTATION_" + std::to_string(_level + 1)))
                    return false;
                return incantate(doAction("Incantation"));
            }
        }

        case ELEVATION_SLAVE: {
            _dock_mode = true;

            logger.log("Waiting elevation signal for level " + std::to_string(_level + 1));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            return true;
        }

        case MEETUP: {
            const Direction dir = _sound_system.getNearestSoundDirection("MEETUP_" + std::to_string(_level + 1));
            if (dir != NONE && dir != HERE) {
                const std::vector<Direction> moves = getMovesTowardsSoundDirection(dir);
                return executeMoves(look, moves);
            }

            logger.log("No one find for the meetup. Defaulting to food searching.");
            return handleGoal(look, "food");
        }

        case MEETUP_POINT: {
            _dock_mode = true;

            logger.log("Sending everyone a point meetup request for level " + std::to_string(_level + 1));
            if (!useBroadcast("MEETUP_" + std::to_string(_level + 1)))
                return false;
            std::this_thread::sleep_for(std::chrono::milliseconds(ACTION_DELAY_MS));
            return true;
        }

        case REPRODUCE: {
            logger.log("Creating an egg.");
            return doAction("Fork") != "dead";
        }

        default:
            logger.log("No specific action for current goal '" + std::to_string(_goal) + "' (Lvl " +
            std::to_string(_level) + "). Wandering.");
            return performWanderAction();
    }
}
