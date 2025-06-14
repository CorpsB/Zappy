// include/Camera.hpp
#pragma once
#include "Math.hpp"

namespace Renderer {
    // Caméra
    extern Vec3 cameraPosition;
    extern float cameraPitch;
    extern float cameraYaw;
    extern float cameraSpeed;
    extern float cameraRotationSpeed;

    // Outils caméra
    Mat4x4 pointAt(const Vec3& pos, const Vec3& target, const Vec3& up);
    Mat4x4 quickInverse(const Mat4x4& m);

    // Entrée utilisateur
    void processInput(float dt);
}