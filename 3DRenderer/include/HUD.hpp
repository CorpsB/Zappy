// include/HUD.hpp
#pragma once
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "Math.hpp"

namespace Renderer {
    struct HudMessage {
        std::string text;
        float remainingTime;
    };

    extern std::list<HudMessage> hudMessages;
    void displayText(const std::string& message, float duration);
}