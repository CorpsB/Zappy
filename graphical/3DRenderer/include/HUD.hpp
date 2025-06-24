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
    extern std::deque<std::string> histInstruc;
    void displayText(const std::string& message, float duration);
}