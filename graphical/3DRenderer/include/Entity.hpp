// include/Entity.hpp
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Geometry.hpp"
#include "Math.hpp"
#include <unordered_map>
#include <array>

namespace Renderer {
    enum class EntityType { CUBE, SPHERE, STL };
    enum class PartType { BODY, EYES, GROUND, Q0, Q1, Q2, Q3, Q4, Q5, Q6 };
    enum class Compass { NORTH, EAST, SOUTH, WEST };

    struct MovementState {
        Vec3 direction;       // direction de déplacement (normalisée * 5.5)
        float timeElapsed = 0.f; // Temps depuis la dernière étape
        int stepsRemaining = 0;  // Nombre d'étapes restantes
        bool active = false;
    };

    struct RotationState {
        float totalRotated = 0.f;
        float timeElapsed = 0.f;
        int stepsRemaining = 0.f;
        bool active = false;
        bool goingRight; // true or false (= going left)
    };

    struct Entity {
        int id;
        PartType type;
        int clientId;
        Mesh mesh;
        Vec3 position;
        Compass orientation;
        Vec3 rotation;
        Vec3 scale;
        int level;
    };

    extern std::vector<Entity> sceneEntities;
    extern int nextEntityID;
    extern int rotatingEntityId;
    extern std::array<std::string, 8> pathEyes;
    extern std::array<float, 8> offsetEyesZ;

    // Création d'entités
    int spawn(EntityType type, PartType partType, int clientId, const Vec3& pos,
              const sf::Color& c, const std::string& filepath = "", Compass orientation = Compass::NORTH,
              const Vec3& rotation = {0.f, 0.f, 0.f}, int level = -1);
    float compassToAngle(Renderer::Compass c);
}
