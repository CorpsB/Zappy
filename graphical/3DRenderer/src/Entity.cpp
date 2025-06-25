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
    std::array<std::string, 8> pathEyes = {
        "./Assets/Eyes_lv1.stl",
        "./Assets/Eyes_lv2.stl",
        "./Assets/Eyes_lv3.stl",
        "./Assets/Eyes_lv4.stl",
        "./Assets/Eyes_lv5.stl",
        "./Assets/Eyes_lv6.stl",
        "./Assets/Eyes_lv7.stl",
        "./Assets/Eyes_lv8.stl"
    };
    std::array<float, 8> offsetEyesZ = {
        -8.8f,
        -7.8f,
        -8.2f,
        -5.5f,
        -7.5f,
        -6.5f,
        -7.2f,
        -6.4f
    };

    int spawn(EntityType type, PartType partType, int clientId, const Vec3& pos,
              const sf::Color& c, const std::string& filepath, Compass orientation,
              const Vec3& rotation, int level, std::string teamName) {
        Entity newEnt;
        newEnt.id = nextEntityID++;
        newEnt.type = partType;
        newEnt.clientId = clientId;
        newEnt.position = pos;
        newEnt.rotation = rotation;
        newEnt.scale    = {1.f, 1.f, 1.f};
        newEnt.orientation = orientation;
        newEnt.level = level;
        newEnt.teamName = teamName;
        newEnt.color = c;
        // newEnt.rotation.y = compassToAngle(orientation);
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

    float compassToAngle(Renderer::Compass c) {
        switch (c) {
            case Renderer::Compass::NORTH: return 0.f;
            case Renderer::Compass::EAST:  return 90.f;
            case Renderer::Compass::SOUTH: return 180.f;
            case Renderer::Compass::WEST:  return 270.f;
        }
        return 0.f;
    }

} // namespace Renderer
