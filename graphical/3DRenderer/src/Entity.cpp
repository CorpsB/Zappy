/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Entity
*/

#include "Entity.hpp"
#include "Geometry.hpp"
#include "STLLoader.hpp"
#include <iostream>
#include <stdexcept>

namespace Renderer {

    std::vector<Entity> sceneEntities;
    int nextEntityID = 0;
    int rotatingEntityId = -1;

    int spawn(EntityType type, PartType partType, int clientId, const Vec3& pos,
              const sf::Color& c, const std::string& filepath, Compass orientation) {
        Entity newEnt;
        newEnt.id = nextEntityID++;
        newEnt.type = partType;
        newEnt.clientId = clientId;
        newEnt.position = pos;
        newEnt.rotation = {0.f, 0.f, 0.f};
        newEnt.scale    = {1.f, 1.f, 1.f};
        newEnt.orientation = orientation;

        switch (orientation)
        {
        case Compass::NORTH:
            newEnt.rotation.y = 0.f;
            break;
        case Compass::EAST:
            newEnt.rotation.y = 90.f;
            break;
        case Compass::SOUTH:
            newEnt.rotation.y = 180.f;
            break;
        case Compass::WEST:
            newEnt.rotation.y = 270.f;
            break;
        default:
            break;
        }
        try {
            switch (type) {
            case EntityType::CUBE:
                newEnt.mesh = createCubeMesh(c);
                break;
            case EntityType::SPHERE:
                newEnt.mesh = createSphereMesh(c);
                break;
            case EntityType::STL:
                if (filepath.empty())
                    throw std::runtime_error("STL type requires a filepath.");
                newEnt.mesh = createSTLMesh(filepath, c);
                break;
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return -1;
        }

        sceneEntities.push_back(newEnt);
        return newEnt.id;
    }

} // namespace Renderer