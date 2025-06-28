/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** HUD
*/

#include "HUD.hpp"

namespace Renderer {

    std::list<HudMessage> hudMessages;
    std::deque<std::tuple<std::string, sf::Color>> histInstruc;

    void displayText(const std::string& message, float duration) {
        hudMessages.push_back({message, duration});
    }

} // namespace Renderer