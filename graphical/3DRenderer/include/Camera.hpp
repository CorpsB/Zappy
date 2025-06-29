/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Camera
*/

#pragma once

#include "Math.hpp"
#include "Renderer.hpp"
#include <SFML/Window.hpp>
#include <cmath>
#include "InputHandler.hpp"

namespace Renderer {
    class Camera {
        public:
            Camera();
            ~Camera() = default;
            // Outils caméra
            Mat4x4 pointAt(const Vec3& pos, const Vec3& target, const Vec3& up);
            Mat4x4 quickInverse(const Mat4x4& m);

            // Entrée utilisateur
            void cameraMovement(float dt);
            Vec3 getPosition() const;
            float getPitch() const;
            float getYaw() const;
            float getSpeed() const;
            float getRotationSpeed() const;
            void setPosition(const Vec3 pos);
        private:
            Vec3 cameraPosition;
            float cameraPitch;
            float cameraYaw;
            float cameraSpeed;
            float cameraRotationSpeed;

    };
}
