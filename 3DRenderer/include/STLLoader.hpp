// include/STLLoader.hpp
#pragma once
#include <string>
#include <fstream>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "Geometry.hpp"

namespace Renderer {
    // Chargement STL
    bool isBinarySTL(std::ifstream& file, const std::string& filename, uint32_t& triCount);
    void loadBinarySTL(std::ifstream& file, Mesh& mesh, uint32_t triCount, const sf::Color& c);
    void loadAsciiSTL(std::ifstream& file, Mesh& mesh, const sf::Color& c);
    void centerMesh(Mesh& mesh);
    Mesh createSTLMesh(const std::string& filename, const sf::Color& c);
}