/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** collect_item
*/

#include "../../AI.hpp"
#include "../../../utils/utils.hpp"

bool ai::entity::AI::collectItem(const std::string &look, const std::string &name, int recipe_qty)
{
    int pos = findItemInLook(look, name);

    if (pos == -1)
        return false;
    if (pos != 0)
        return true;
    if ((name == "food" && _food_level >= 12.0) || _level == 8 ||
    (name != "food" && _inventory.getItem(name) >= recipe_qty * 2 + 1))
        return true;
    return _socket.doAction("Take " + name) != "dead";
}

bool ai::entity::AI::collectAllItems(const std::string &look)
{
    return collectItem(look, "food", _food_level) &&
    collectItem(look, "linemate", RECIPES[_level - 1].linemate) &&
    collectItem(look, "deraumere", RECIPES[_level - 1].deraumere) &&
    collectItem(look, "sibur", RECIPES[_level - 1].sibur) &&
    collectItem(look, "mendiane", RECIPES[_level - 1].mendiane) &&
    collectItem(look, "phiras", RECIPES[_level - 1].phiras) &&
    collectItem(look, "thystame", RECIPES[_level - 1].thystame);
}
