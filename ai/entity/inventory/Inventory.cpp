/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Inventory
*/

#include "Inventory.hpp"
#include "../../utils/utils.hpp"
#include <stdexcept>
#include <algorithm>

ai::entity::Inventory::Inventory()
{
    _storage["food"] = 0;
    _storage["linemate"] = 0;
    _storage["deraumere"] = 0;
    _storage["sibur"] = 0;
    _storage["mendiane"] = 0;
    _storage["phiras"] = 0;
    _storage["thystame"] = 0;
}

bool ai::entity::Inventory::update(const std::string &storage)
{
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();

    if (storage.empty() || storage.front() != '[' || storage.back() != ']') {
        logger.log("[Error] Bad inventory format.");
        return false;
    }

    const std::string content = storage.substr(1, storage.size() - 2);
    std::vector<std::string> items = utils::string::split(content, ',');

    for (std::string &item : items) {
        item.erase(std::remove_if(item.begin(), item.end(), ::isspace), item.end());

        const size_t pos = std::find_if(item.begin(), item.end(), ::isdigit) - item.begin();
        if (pos == std::string::npos || pos == 0) {
            logger.log("[Error] Unset item quantity : " + item);
            return false;
        }
        const std::string resource = item.substr(0, pos);
        const std::string quantity = item.substr(pos);

        setItem(resource, std::stoi(quantity));
    }
}

void ai::entity::Inventory::setItem(const std::string &item, int quantity)
{
    const int value = getItem(item);

    if (value == -1) {
        utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
        logger.log("[Error] Unknown item to set '" + item + "'");
        return;
    }
    _storage[item] = quantity;
}

int ai::entity::Inventory::getItem(const std::string &item)
{
    try {
        const int value = _storage.at(item);
        return value;
    } catch (std::out_of_range) {
        return -1;
    }
}
