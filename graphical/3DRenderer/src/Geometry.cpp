/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Geometry
*/

#include "Geometry.hpp"
#include <cmath>
#include <vector>

namespace Renderer {

Mesh createCubeMesh(const sf::Color& c) {
    Mesh mesh;
    mesh.tris = {
        {{Vec3{-0.5f,-0.5f,-0.5f}, Vec3{-0.5f, 0.5f,-0.5f}, Vec3{ 0.5f, 0.5f,-0.5f}}, c},
        {{Vec3{-0.5f,-0.5f,-0.5f}, Vec3{ 0.5f, 0.5f,-0.5f}, Vec3{ 0.5f,-0.5f,-0.5f}}, c},
        {{Vec3{ 0.5f,-0.5f,-0.5f}, Vec3{ 0.5f, 0.5f,-0.5f}, Vec3{ 0.5f, 0.5f, 0.5f}}, c},
        {{Vec3{ 0.5f,-0.5f,-0.5f}, Vec3{ 0.5f, 0.5f, 0.5f}, Vec3{ 0.5f,-0.5f, 0.5f}}, c},
        {{Vec3{ 0.5f,-0.5f, 0.5f}, Vec3{ 0.5f, 0.5f, 0.5f}, Vec3{-0.5f, 0.5f, 0.5f}}, c},
        {{Vec3{ 0.5f,-0.5f, 0.5f}, Vec3{-0.5f, 0.5f, 0.5f}, Vec3{-0.5f,-0.5f, 0.5f}}, c},
        {{Vec3{-0.5f,-0.5f, 0.5f}, Vec3{-0.5f, 0.5f, 0.5f}, Vec3{-0.5f, 0.5f,-0.5f}}, c},
        {{Vec3{-0.5f,-0.5f, 0.5f}, Vec3{-0.5f, 0.5f,-0.5f}, Vec3{-0.5f,-0.5f,-0.5f}}, c},
        {{Vec3{-0.5f, 0.5f,-0.5f}, Vec3{-0.5f, 0.5f, 0.5f}, Vec3{ 0.5f, 0.5f, 0.5f}}, c},
        {{Vec3{-0.5f, 0.5f,-0.5f}, Vec3{ 0.5f, 0.5f, 0.5f}, Vec3{ 0.5f, 0.5f,-0.5f}}, c},
        {{Vec3{ 0.5f,-0.5f, 0.5f}, Vec3{-0.5f,-0.5f, 0.5f}, Vec3{-0.5f,-0.5f,-0.5f}}, c},
        {{Vec3{ 0.5f,-0.5f, 0.5f}, Vec3{-0.5f,-0.5f,-0.5f}, Vec3{ 0.5f,-0.5f,-0.5f}}, c}
    };
    return mesh;
}

Mesh createSphereMesh(const sf::Color& c, int subdivisions) {
    Mesh mesh;
    auto normalize = [](Vec3 v) {
        float l = std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
        return (l > 0) ? Vec3{v.x/l, v.y/l, v.z/l} : v;
    };
    const float t = (1.0f + std::sqrt(5.0f)) / 2.0f;
    std::vector<Vec3> vertices = {
        normalize({-1,  t,  0}), normalize({ 1,  t,  0}), normalize({-1, -t,  0}), normalize({ 1, -t,  0}),
        normalize({ 0, -1,  t}), normalize({ 0,  1,  t}), normalize({ 0, -1, -t}), normalize({ 0,  1, -t}),
        normalize({ t,  0, -1}), normalize({ t,  0,  1}), normalize({-t,  0, -1}), normalize({-t,  0,  1})
    };
    mesh.tris = {
        {{vertices[0],vertices[11],vertices[5]},c},{{vertices[0],vertices[5],vertices[1]},c},{{vertices[0],vertices[1],vertices[7]},c},
        {{vertices[0],vertices[7],vertices[10]},c},{{vertices[0],vertices[10],vertices[11]},c},{{vertices[1],vertices[5],vertices[9]},c},
        {{vertices[5],vertices[11],vertices[4]},c},{{vertices[11],vertices[10],vertices[2]},c},{{vertices[10],vertices[7],vertices[6]},c},
        {{vertices[7],vertices[1],vertices[8]},c},{{vertices[3],vertices[9],vertices[4]},c},{{vertices[3],vertices[4],vertices[2]},c},
        {{vertices[3],vertices[2],vertices[6]},c},{{vertices[3],vertices[6],vertices[8]},c},{{vertices[3],vertices[8],vertices[9]},c},
        {{vertices[4],vertices[9],vertices[5]},c},{{vertices[2],vertices[4],vertices[11]},c},{{vertices[6],vertices[2],vertices[10]},c},
        {{vertices[8],vertices[6],vertices[7]},c},{{vertices[9],vertices[8],vertices[1]},c}
    };
    for (int i = 0; i < subdivisions; ++i) {
        std::vector<Triangle> subdivided;
        for (const auto& tri : mesh.tris) {
            Vec3 v1 = tri.p[0], v2 = tri.p[1], v3 = tri.p[2];
            Vec3 m1 = normalize({(v1.x+v2.x)/2,(v1.y+v2.y)/2,(v1.z+v2.z)/2});
            Vec3 m2 = normalize({(v2.x+v3.x)/2,(v2.y+v3.y)/2,(v2.z+v3.z)/2});
            Vec3 m3 = normalize({(v3.x+v1.x)/2,(v3.y+v1.y)/2,(v3.z+v1.z)/2});
            subdivided.push_back({{v1,m1,m3},c});
            subdivided.push_back({{v2,m2,m1},c});
            subdivided.push_back({{v3,m3,m2},c});
            subdivided.push_back({{m1,m2,m3},c});
        }
        mesh.tris = std::move(subdivided);
    }
    return mesh;
}

} // namespace Renderer