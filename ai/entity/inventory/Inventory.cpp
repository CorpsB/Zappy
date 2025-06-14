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

void ai::entity::Inventory::update(const std::string &storage)
{
    if (storage.empty() || storage.front() != '[' || storage.back() != ']')
        throw utils::exception::Error("INVENTORY", "Bad inventory format.");
    
    const std::string content = storage.substr(1, storage.size() - 2);
    std::vector<std::string> items = utils::string::split(content, ',');

    for (std::string &item : items) {
        // delete spaces
        item.erase(std::remove_if(item.begin(), item.end(), ::isspace), item.end());

        const size_t pos = std::find_if(item.begin(), item.end(), ::isdigit) - item.begin();
        if (pos == std::string::npos || pos == 0)
            throw utils::exception::Error("INVENTORY", "Unset item quantity : " + item);

        const std::string resource = item.substr(0, pos);
        const std::string quantity = item.substr(pos);

        setItem(resource, std::stoi(quantity));
    }
}

void ai::entity::Inventory::setItem(const std::string &item, int quantity)
{
    int value = getItem(item);

    if (value == -1)
        throw utils::exception::Error("INVENTORY", "Unknown item to set '" + item + "'");
    _storage[item] = quantity;
}

int ai::entity::Inventory::getItem(const std::string &item)
{
    int value;

    try {
        value = _storage.at(item);
    } catch (std::out_of_range) {
        value = -1;
    }
    return value;
}
