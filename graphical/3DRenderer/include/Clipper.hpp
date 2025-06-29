/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Clipper
*/

#pragma once

#include "Math.hpp"
#include "Geometry.hpp"
#include <algorithm>

namespace Renderer {
    // Clipping contre un plan
    class Clipper {
        public:
            Clipper() = default;
            ~Clipper() = default;
            Vec3 vectorIntersectPlane(const Vec3& p_p, const Vec3& p_n, const Vec3& lS, const Vec3& lE);
            int clipAgainstPlane(const Vec3& p_p, const Vec3& p_n, const Triangle& in, Triangle& out1, Triangle& out2);
    };
}
