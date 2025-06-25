// include/Clipper.hpp
#pragma once
#include "Math.hpp"
#include "Geometry.hpp"

namespace Renderer {
    // Clipping contre un plan
    Vec3 vectorIntersectPlane(const Vec3& p_p, const Vec3& p_n, const Vec3& lS, const Vec3& lE);
    int clipAgainstPlane(const Vec3& p_p, const Vec3& p_n, const Triangle& in, Triangle& out1, Triangle& out2);
}
