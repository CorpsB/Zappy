/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** STLLoader
*/

#include "STLLoader.hpp"
#include <filesystem>

namespace Renderer {

    bool isBinarySTL(std::ifstream& file, const std::string& filename, uint32_t& triCount) {
        char header[80];
        file.read(header, 80);
        if (!file) return false;
        file.read(reinterpret_cast<char*>(&triCount), sizeof(triCount));
        if (!file) {
            file.clear();
            file.seekg(0, std::ios::beg);
            return false;
        }
        auto size = std::filesystem::file_size(filename);
        uint64_t expected = 80ull + 4ull + uint64_t(triCount) * 50ull;
        return size == expected;
    }

    void loadBinarySTL(std::ifstream& file, Mesh& mesh, uint32_t triCount, const sf::Color& c) {
        for (uint32_t i = 0; i < triCount; ++i) {
            file.ignore(sizeof(float) * 3);
            Vec3 v[3];
            for (int j = 0; j < 3; ++j) {
                float coords[3];
                file.read(reinterpret_cast<char*>(&coords), sizeof(coords));
                v[j] = {-coords[0], coords[2], coords[1]};
            }
            file.ignore(2);
            mesh.tris.push_back({{v[0], v[1], v[2]}, c});
        }
    }

    void loadAsciiSTL(std::ifstream& file, Mesh& mesh, const sf::Color& c) {
        file.clear();
        file.seekg(0, std::ios::beg);
        std::string line;
        Vec3 verts[3];
        int idx = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string tok;
            iss >> tok;
            std::transform(tok.begin(), tok.end(), tok.begin(), ::tolower);
            if (tok == "vertex") {
                iss >> verts[idx].x >> verts[idx].z >> verts[idx].y;
                if (++idx == 3) {
                    std::swap(verts[1], verts[2]);
                    mesh.tris.push_back({{verts[0], verts[1], verts[2]}, c});
                    idx = 0;
                }
            }
        }
    }

    void centerMesh(Mesh& mesh) {
        if (mesh.tris.empty()) return;
        float minX = 1e9f, minY = 1e9f, minZ = 1e9f;
        float maxX = -1e9f, maxY = -1e9f, maxZ = -1e9f;
        for (const auto& tri : mesh.tris) {
            for (const auto& v : tri.p) {
                minX = std::min(minX, v.x);
                minY = std::min(minY, v.y);
                minZ = std::min(minZ, v.z);
                maxX = std::max(maxX, v.x);
                maxY = std::max(maxY, v.y);
                maxZ = std::max(maxZ, v.z);
            }
        }
        Vec3 center = {(minX + maxX) * 0.5f, (minY + maxY) * 0.5f, (minZ + maxZ) * 0.5f};
        for (auto& tri : mesh.tris) {
            for (auto& v : tri.p) {
                v.x -= center.x;
                v.y -= center.y;
                v.z -= center.z;
            }
        }
    }

    Mesh createSTLMesh(const std::string& filename, const sf::Color& c) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) throw std::runtime_error("Impossible d'ouvrir STL: " + filename);
        Mesh mesh;
        uint32_t triCount = 0;
        if (isBinarySTL(file, filename, triCount)) {
            loadBinarySTL(file, mesh, triCount, c);
        } else {
            loadAsciiSTL(file, mesh, c);
        }
        centerMesh(mesh);
        return mesh;
    }
}
