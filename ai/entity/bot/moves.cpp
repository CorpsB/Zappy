/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** moves
*/

#include "../AI.hpp"
#include <thread>

std::string ai::entity::AI::getDirectionName(Direction dir)
{
    switch (dir) {
        case UP:
            return "Forward";
        case LEFT:
            return "Left";
        case RIGHT:
            return "Right";
        default:
            return "";
    }
}

std::vector<ai::entity::Direction> ai::entity::AI::getMovesToTileLevel1Vision(int idx)
{
    switch (idx) {
        case 0:
            return {NONE};
        case 1:
            return {UP, LEFT, UP};
        case 2:
            return {UP};
        case 3:
            return {UP, RIGHT, UP};
        default:
            return {};
    }
}

std::vector<ai::entity::Direction> ai::entity::AI::getMovesTowardsSoundDirection(Direction dir)
{
    switch (dir) {
        case HERE:
            return {NONE};
        case UP:
            return {UP};
        case UP_LEFT:
            return {UP, LEFT, UP};
        case UP_RIGHT:
            return {UP, RIGHT, UP};
        case LEFT:
            return {LEFT, UP};
        case RIGHT:
            return {RIGHT, UP};
        case DOWN:
            return {LEFT, LEFT, UP};
        case DOWN_LEFT:
            return {LEFT, UP, LEFT, UP};
        case DOWN_RIGHT:
            return {RIGHT, UP, RIGHT, UP};
        default:
            return {};
    }
}

bool ai::entity::AI::executeMoves(const std::string &look, const std::vector<Direction> &moves)
{
    for (const auto &move : moves) {
        if (!collectAllItems(look))
            return false;
        if (move != UP && move != LEFT && move != RIGHT) {
            utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
            logger.log("[Error] Unknown move " + std::to_string(move));
            return false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(ACTION_DELAY_MS));

        const std::string move_str = getDirectionName(move);
        if (doAction(move_str) == "dead")
            return false;

        std::this_thread::sleep_for(std::chrono::milliseconds(ACTION_DELAY_MS));
    }
    return true;
}

bool ai::entity::AI::executeSpiralMove(SpiralState &state)
{
    std::string action_to_take;

    if (state.leg_steps_taken < state.leg_max_steps) {
        action_to_take = "Forward";
        state.leg_steps_taken++;
    } else {
        action_to_take = "Left";
        state.leg_steps_taken = 0;
        state.legs_completed_at_current_length++;

        if (state.legs_completed_at_current_length >= 2) {
            state.leg_max_steps++;
            state.legs_completed_at_current_length = 0;
        }
    }

    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
    logger.log("Search Spiral Action: " + action_to_take);
    return doAction(action_to_take) != "dead";
}
