// include/HUD.hpp
#pragma once
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "Math.hpp"
#include <queue>

namespace Renderer {
    struct HudMessage {
        std::string text;
        float remainingTime;
    };

    extern std::list<HudMessage> hudMessages;
    extern std::deque<std::tuple<std::string, sf::Color>> histInstruc;
    void displayText(const std::string& message, float duration);
}
