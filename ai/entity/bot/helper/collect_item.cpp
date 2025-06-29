/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** collect_item
*/

/**
 * @file collect_item.cpp
 * @brief Implementation of item collection functions.
 * @date 29/06/2025
 * @author Jason KOENIG
 *
 * @see AI.hpp
 */

#include "../../AI.hpp"
#include "../../../utils/utils.hpp"

bool ai::entity::AI::collectItem(const std::string &look, const std::string &name,
    int recipe_qty, bool is_players)
{
    int pos = findItemInLook(look, name);

    if (pos == -1)
        return false;
    if (pos != 0)
        return true;
    if ((name == "food" && _food_level >= MAX_FOOD_THRESHOLD) || _level == 8 ||
    (name != "food" && _inventory.getItem(name) >= recipe_qty * 2 + 1) || is_players)
        return true;
    return doKoAction("Take " + name);
}

bool ai::entity::AI::collectAllItems(const std::string &look)
{
    const bool is_player = countItemOnTile(0, look, "player") > 0;

    return collectItem(look, "food", _food_level, is_player) &&
    collectItem(look, "linemate", RECIPES[_level - 1].linemate, is_player) &&
    collectItem(look, "deraumere", RECIPES[_level - 1].deraumere, is_player) &&
    collectItem(look, "sibur", RECIPES[_level - 1].sibur, is_player) &&
    collectItem(look, "mendiane", RECIPES[_level - 1].mendiane, is_player) &&
    collectItem(look, "phiras", RECIPES[_level - 1].phiras, is_player) &&
    collectItem(look, "thystame", RECIPES[_level - 1].thystame, is_player);
}
