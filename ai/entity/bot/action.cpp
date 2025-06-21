/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** action
*/

#include "../AI.hpp"

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

bool ai::entity::AI::performActionForGoal(const std::string &look)
{
    utils::debug::Logger &logger = ai::utils::debug::Logger::GetInstance();

    switch (_goal) {
        case FOOD:
            return handleGoal(look, "food");

        case STONE: {
            const std::string rarest_missing = getRarestMissingStone();
            return handleGoal(look, rarest_missing);
        }

        case ELEVATION: {
            const std::string broadcast_msg = "Broadcast EVOLVE_" + std::to_string(_level + 1);
            if (doAction(broadcast_msg) == "dead")
                return false;

            const std::vector<Direction> moves = getMovesTowardsSoundDirection(_sound_system.getNearestSoundDirection());
            return executeMoves(look, moves);
        }

        case MEETUP: {
            logger.log("Sending everyone a meetup request for level " + std::to_string(_level + 1));

            const std::string broadcast_msg = "Broadcast MEETUP_" + std::to_string(_level + 1);
            if (doAction(broadcast_msg) == "dead")
                return false;

            const Direction dir = _sound_system.getNearestSoundDirection();
            if (dir != NONE && dir != HERE) {
                const std::vector<Direction> moves = getMovesTowardsSoundDirection(dir);
                return executeMoves(look, moves);
            }
            return handleGoal(look, "food");
        }

        default:
            logger.log("No specific action for current goal '" + std::to_string(_goal) + "' (Lvl " +
            std::to_string(_level) + "). Wandering.");
            return performWanderAction();
    }
}
