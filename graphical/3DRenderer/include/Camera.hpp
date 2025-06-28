// include/Camera.hpp
#pragma once
#include "Math.hpp"
#include "Renderer.hpp"

namespace Renderer {
    // Caméra
    extern Vec3 cameraPosition;
    extern float cameraPitch;
    extern float cameraYaw;
    extern float cameraSpeed;
    extern float cameraRotationSpeed;
    extern bool buttonToggle;
    extern bool buttonIsPressed;
    extern bool escapeMenuToggle;
    extern bool escapeWasPressed;
    extern bool zToggle;
    extern bool zWasPressed;
    extern bool sToggle;
    extern bool sWasPressed;
    extern bool qToggle;
    extern bool qWasPressed;
    extern bool dToggle;
    extern bool dWasPressed;
    extern bool tabToggle;
    extern bool tabWasPressed;
    // Outils caméra
    Mat4x4 pointAt(const Vec3& pos, const Vec3& target, const Vec3& up);
    Mat4x4 quickInverse(const Mat4x4& m);

    // Entrée utilisateur
    void processInput(float dt);
}
