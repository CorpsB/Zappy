// include/Renderer.hpp
#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Camera.hpp"
#include "Entity.hpp"
#include "Clipper.hpp"
#include "Geometry.hpp"
#include "HUD.hpp"
#include "Math.hpp"

namespace Renderer {
    // Initialisation et boucle
    bool initRenderer(int width, int height, const std::string& title);
    void update(float dt);
    void render(float dt);

    bool getIsRunning();
    void shutdownRenderer();
}