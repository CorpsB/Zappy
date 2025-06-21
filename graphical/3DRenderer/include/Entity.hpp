// include/Entity.hpp
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Geometry.hpp"
#include "Math.hpp"
#include <unordered_map>

namespace Renderer {
    enum class EntityType { CUBE, SPHERE, STL };
    enum class PartType { BODY, EYES, GROUND };
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
        int stepsRemaining = 20;
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
    };

    extern std::vector<Entity> sceneEntities;
    extern int nextEntityID;
    extern int rotatingEntityId;

    // Création d'entités
    int spawn(EntityType type, PartType partType, int clientId, const Vec3& pos,
              const sf::Color& c, const std::string& filepath = "", Compass orientation = Compass::NORTH);
    float compassToAngle(Renderer::Compass c);
}
