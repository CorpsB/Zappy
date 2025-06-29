/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Update
*/

#include "Update.hpp"

namespace Renderer
{
    //A function useful for update
    Vec3 Update::rotateY(const Vec3& v, float angleDegrees)
    {
        float angleRad = angleDegrees * (3.14159265f / 180.f);
        float cosA = std::cos(angleRad);
        float sinA = std::sin(angleRad);

        return {
            v.x * cosA - v.z * sinA,
            v.y,
            v.x * sinA + v.z * cosA
        };
    }

    void Update::moveTrantorian(float dt, Entity &e, std::unordered_map<int, MovementState> &activeMovements,
        int map_size_x, int map_size_y)
    {
        auto itMove = activeMovements.find(e.clientId);
        if (itMove != activeMovements.end() && itMove->second.active) {
            MovementState& m = itMove->second;
            m.timeElapsed += dt;
            // X axis wrap
            if (e.position.x < -35.f) {
                e.position.x = (map_size_x - 1) * TILE_SIZE + 35.f + (35.f + e.position.x);
            } else if (e.position.x > (map_size_x - 1) * TILE_SIZE + 35.f) {
                e.position.x = (map_size_x - 1) * TILE_SIZE - e.position.x;
            }

            // Z axis wrap
            if (e.position.z < -35.f) {
                e.position.z = (map_size_y - 1) * TILE_SIZE + 35.f + (35.f + e.position.z);
            } else if (e.position.z > (map_size_y - 1) * TILE_SIZE + 35.f) {
                e.position.z = (map_size_y - 1) * TILE_SIZE - e.position.z;
            }
            while (m.stepsRemaining > 0 && m.timeElapsed >= 0.025f) {
                m.timeElapsed -= 0.025f;

                // Appliquer un déplacement de 5.5 dans la bonne direction
                e.position.x += m.direction.x;
                e.position.y += m.direction.y;
                e.position.z += m.direction.z;

                m.stepsRemaining--;

                if (m.stepsRemaining == 0)
                    m.active = false;
            }
        }
    }
    void Update::rotateTrantorian(float dt, Entity &e, std::unordered_map<int, RotationState> &activeRotations)
    {
        auto itRot = activeRotations.find(e.clientId);
        if (itRot != activeRotations.end() && itRot->second.active) {
            RotationState& r = itRot->second;
            r.timeElapsed += dt;
            while (r.stepsRemaining > 0 && r.timeElapsed >= 0.025f) {
                r.timeElapsed -= 0.025f;
                if (r.goingRight) {
                    e.rotation.y -= 9.f;
                    r.totalRotated -= 9.f;
                } else {
                    e.rotation.y += 9.f;
                    r.totalRotated += 9.f;
                }
                r.stepsRemaining--;

                if (r.stepsRemaining == 0) {
                    r.active = false;
                    // Reset if more than 360° or less than 0°
                    if (e.rotation.y >= 360.f)
                        e.rotation.y -= 360.f;
                    else if (e.rotation.y < 0.f)
                        e.rotation.y += 360.f;
                }
            }
        }
    }

    void Update::startMoveAfterRotate(std::unordered_map<int, MovementState> &activeMovements,
        std::unordered_map<int, RotationState> &activeRotations, std::unordered_map<int, MovementState> &pendingMovementsAfterRotation)
    {
        // Fin de rotation -> on démarre le mouvement
        for (auto it = activeRotations.begin(); it != activeRotations.end(); ++it) {
            int clientId = it->first;
            if (!it->second.active && pendingMovementsAfterRotation.contains(clientId)) {
                activeMovements[clientId] = pendingMovementsAfterRotation[clientId];
                pendingMovementsAfterRotation.erase(clientId);
            }
        }
    }

    void Update::sychroEyes(Entity &e, std::vector<std::tuple<int, Vec3, Vec3>> &valuesForSynchro)
    {
        Vec3 offset = {0.f, OFFSET_EYES_Y, offsetEyesZ[e.level - 1]};
        if (e.type == PartType::BODY) {
            valuesForSynchro.emplace_back(e.clientId, e.position, Vec3{0.f, e.rotation.y, 0.f});
        }
        if (e.type == Renderer::PartType::EYES) {
            // Searching for the corresponding body
            auto it = std::find_if(
                valuesForSynchro.begin(), valuesForSynchro.end(),
                [&e](const std::tuple<int, Vec3, Vec3>& t) {
                    return std::get<0>(t) == e.clientId;
                });

            if (it != valuesForSynchro.end()) {
                Vec3 bodyPos = std::get<1>(*it);
                float bodyRotY = std::get<2>(*it).y;
                Vec3 rotatedOffset = rotateY(offset, bodyRotY);
                e.position = {
                    bodyPos.x + rotatedOffset.x,
                    bodyPos.y + rotatedOffset.y,
                    bodyPos.z + rotatedOffset.z
                };
                e.rotation.y = bodyRotY;
            }
        }
    }

    void Update::incantationRing(float dt, Entity &e)
    {
        if (e.type == PartType::RING) {
            e.rotation.y += 20.0f * dt;
            if (e.rotation.y >= 360.f)
                e.rotation.y -= 360.f;
        }
    }

    void Update::changeSelectedTile(bool &zToggle, bool &sToggle, bool &qToggle, bool &dToggle,
        std::pair<int, int> &currentTile, int map_size_x, int map_size_y)
    {
        if (zToggle) {
            if (currentTile.first < map_size_x - 1)
                currentTile.first += 1;
            zToggle = false;
        }
        if (sToggle) {
            if (currentTile.first > 0)
                currentTile.first -= 1;
            sToggle = false;
        }
        if (qToggle) {
            if (currentTile.second < map_size_y - 1)
                currentTile.second += 1;
            qToggle = false;
        }
        if (dToggle) {
            if (currentTile.second > 0)
                currentTile.second -= 1;
            dToggle = false;
        }
    }
} // namespace Renderer
