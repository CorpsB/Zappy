/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Camera
*/

#include "Camera.hpp"
#include <SFML/Window.hpp>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

namespace Renderer {

    Vec3 cameraPosition = {0.0f, 1.0f, -5.0f};
    float cameraPitch = 0.0f;
    float cameraYaw = 0.0f;
    float cameraSpeed = 15.0f;
    float cameraRotationSpeed = 60.0f;

    Mat4x4 pointAt(const Vec3& pos, const Vec3& target, const Vec3& up) {
        return Mat4x4::pointAt(pos, target, up);
    }

    Mat4x4 quickInverse(const Mat4x4& m) {
        return Mat4x4::quickInverse(m);
    }

    void processInput(float dt) {
        float move = cameraSpeed * dt;
        float rot  = cameraRotationSpeed * dt;

        Vec3 forward = { static_cast<float>(std::sin(cameraYaw * M_PI / 180.0f)), 0.0f, static_cast<float>(std::cos(cameraYaw * M_PI / 180.0f)) };
        Vec3 right   = { forward.z, 0.0f, -forward.x };
        
        // Mouvements
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    { cameraPosition.x += forward.x * move * 3; cameraPosition.z += forward.z * move * 3; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  { cameraPosition.x -= forward.x * move; cameraPosition.z -= forward.z * move; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  { cameraPosition.x -= right.x   * move; cameraPosition.z -= right.z   * move; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { cameraPosition.x += right.x   * move; cameraPosition.z += right.z   * move; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { cameraPosition.y -= move; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))     { cameraPosition.y += move; }

        // Rotations
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { cameraYaw   -= rot; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { cameraYaw   += rot; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { cameraPitch += rot; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) { cameraPitch -= rot; }

    }

} // namespace Renderer
