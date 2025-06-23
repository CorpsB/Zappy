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

#define TILE_SIZE 70
#define OFFSET_EYES_Y -1.5f

namespace Renderer {
    // Initialisation et boucle
    bool initRenderer(sf::RenderWindow &window);
    Vec3 rotateY(const Vec3& v, float angleDegrees);
    void update(float dt);
    void render(float dt, sf::RenderWindow &window);
    // bool getIsRunning();
    // void shutdownRenderer();

    extern std::unordered_map<int, MovementState> activeMovements;
    extern std::unordered_map<int, RotationState> activeRotations;
    extern std::unordered_map<int, Renderer::MovementState> pendingMovementsAfterRotation;
    extern int map_size_x;
    extern int map_size_y;

}