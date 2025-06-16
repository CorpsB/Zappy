// include/Entity.hpp
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Geometry.hpp"
#include "Math.hpp"

namespace Renderer {
    enum class EntityType { CUBE, SPHERE, STL };
    enum class PartType { BODY, EYES, GROUND };

    struct Entity {
        int id;
        PartType type;
        int clientId;
        Mesh mesh;
        Vec3 position;
        Vec3 rotation;
        Vec3 scale;
    };

    extern std::vector<Entity> sceneEntities;
    extern int nextEntityID;
    extern int rotatingEntityId;

    // Création d'entités
    int spawn(EntityType type, PartType partType, int clientId, const Vec3& pos, const sf::Color& c, const std::string& filepath = "");
}
