// include/Geometry.hpp
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Math.hpp"

namespace Renderer {
    struct Triangle {
        Vec3 p[3];
        sf::Color color;
    };

    struct Mesh {
        std::vector<Triangle> tris;
    };

    // Primitives géométriques
    Mesh createCubeMesh(const sf::Color& c);
    Mesh createSphereMesh(const sf::Color& c, int subdivisions = 2);
}