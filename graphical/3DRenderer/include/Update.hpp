/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Update
*/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Camera.hpp"
#include "Entity.hpp"
#include "Clipper.hpp"
#include "Geometry.hpp"
#include "HUD.hpp"
#include "Math.hpp"
#include "Renderer.hpp"

#define TILE_SIZE 70
#define OFFSET_EYES_Y -1.5f

namespace Renderer {
    class Update {
        public:
            Update() = default;
            ~Update() = default;
            Vec3 rotateY(const Vec3& v, float angleDegrees);
            void moveTrantorian(float dt, Entity &e, std::unordered_map<int, MovementState> &activeMovements);
            void rotateTrantorian(float dt, Entity &e, std::unordered_map<int, RotationState> &activeRotations);
            void startMoveAfterRotate(std::unordered_map<int, MovementState> &activeMovements,
                std::unordered_map<int, RotationState> &activeRotations,
                std::unordered_map<int, MovementState> &pendingMovementsAfterRotation);
            void sychroEyes(Entity &e, std::vector<std::tuple<int, Vec3, Vec3>> &valuesForSynchro);
            void incantationRing(float dt, Entity &e);
        private:
    };
}
