/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Camera
*/

#include "Camera.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

namespace Renderer {

    Camera::Camera()
    {
        this->cameraPosition = {0.0f, 1.0f, -5.0f};
        this->cameraPitch = 0.0f;
        this->cameraYaw = 0.0f;
        this->cameraSpeed = 15.0f;
        this->cameraRotationSpeed = 60.0f;
    }

    Mat4x4 Camera::pointAt(const Vec3& pos, const Vec3& target, const Vec3& up) {
        return Mat4x4::pointAt(pos, target, up);
    }

    Mat4x4 Camera::quickInverse(const Mat4x4& m) {
        return Mat4x4::quickInverse(m);
    }

    void Camera::cameraMovement(float dt)
    {
        float move = cameraSpeed * dt;
        float rot  = cameraRotationSpeed * dt;

        Vec3 forward = { static_cast<float>(std::sin(cameraYaw * M_PI / 180.0f)), 0.0f, static_cast<float>(std::cos(cameraYaw * M_PI / 180.0f)) };
        Vec3 right   = { forward.z, 0.0f, -forward.x };
        
        // Mouvements
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    { cameraPosition.x += forward.x * move * 4; cameraPosition.z += forward.z * move * 4; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  { cameraPosition.x -= forward.x * move * 4; cameraPosition.z -= forward.z * move * 4; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  { cameraPosition.x -= right.x   * move * 4; cameraPosition.z -= right.z   * move * 4; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { cameraPosition.x += right.x   * move * 4; cameraPosition.z += right.z   * move * 4; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { cameraPosition.y -= move; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))     { cameraPosition.y += move; }

        // Rotations
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { cameraYaw   -= rot; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { cameraYaw   += rot; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { cameraPitch += rot; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) { cameraPitch -= rot; }
    }

    Vec3 Camera::getPosition() const
    {
        return this->cameraPosition;
    }

    float Camera::getPitch() const
    {
        return this->cameraPitch;
    }

    float Camera::getYaw() const
    {
        return this->cameraYaw;
    }

    float Camera::getSpeed() const
    {
        return this->cameraSpeed;
    }

    float Camera::getRotationSpeed() const
    {
        return this->cameraRotationSpeed;
    }

    void Camera::setPosition(const Vec3 pos)
    {
        this->cameraPosition = pos;
    }

} // namespace Renderer
