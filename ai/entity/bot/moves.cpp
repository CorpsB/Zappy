/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** moves
*/

/**
 * @file moves.cpp
 * @brief Implements movement helper functions for AI navigation.  
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @see AI.hpp
 */

#include "../AI.hpp"

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

std::vector<ai::entity::Direction> ai::entity::AI::getMovesToTileLevelVision(int idx)
{
    std::vector<Direction> moves;
    int depth = 0;
    int total = 0;

    while (true) {
        int width = 2 * depth + 1;
        if (total + width > idx)
            break;
        total += width;
        ++depth;
    }

    const int x = idx - total - depth;
    if (x < 0) {
        moves.push_back(LEFT);
        for (int i = 0; i < -x; ++i)
            moves.push_back(UP);
        moves.push_back(RIGHT);
    } else if (x > 0) {
        moves.push_back(RIGHT);
        for (int i = 0; i < x; ++i)
            moves.push_back(UP);
        moves.push_back(LEFT);
    }
    for (int i = 0; i < depth; ++i)
        moves.push_back(UP);
    return moves;
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

bool ai::entity::AI::executeMoves(std::string &look, const std::vector<Direction> &moves)
{
    for (const auto &move : moves) {
        if (!collectAllItems(look))
            return false;
        if (move != UP && move != LEFT && move != RIGHT) {
            utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
            logger.log("[Error] Unknown move " + std::to_string(move));
            return false;
        }

        const std::string move_str = getDirectionName(move);
        if (doAction(move_str) == "dead")
            return false;

        look = doAction("Look");
        if (look == "dead")
            return false;
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
