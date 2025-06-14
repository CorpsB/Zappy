/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Clipper
*/

#include "Clipper.hpp"
#include <algorithm>

namespace Renderer {
    Vec3 vectorIntersectPlane(const Vec3& p_p, const Vec3& p_n, const Vec3& lS, const Vec3& lE) {
        float p_d = -(p_n.x*p_p.x + p_n.y*p_p.y + p_n.z*p_p.z);
        float ad  = lS.x*p_n.x + lS.y*p_n.y + lS.z*p_n.z;
        float bd  = lE.x*p_n.x + lE.y*p_n.y + lE.z*p_n.z;
        float t   = (-p_d - ad) / (bd - ad);
        Vec3 dir = { lE.x - lS.x, lE.y - lS.y, lE.z - lS.z };
        return { lS.x + dir.x * t, lS.y + dir.y * t, lS.z + dir.z * t };
    }

    int clipAgainstPlane(const Vec3& p_p, const Vec3& p_n, const Triangle& in, Triangle& out1, Triangle& out2) {
        auto dist = [&](const Vec3& p) {
            return p_n.x*p.x + p_n.y*p.y + p_n.z*p.z - (p_n.x*p_p.x + p_n.y*p_p.y + p_n.z*p_p.z);
        };
        const Vec3* inside[3]; int nIn = 0;
        const Vec3* outside[3]; int nOut = 0;

        for (int i = 0; i < 3; ++i) {
            if (dist(in.p[i]) >= 0) inside[nIn++] = &in.p[i];
            else                  outside[nOut++] = &in.p[i];
        }
        if (nIn == 0) return 0;
        if (nIn == 3) { out1 = in; return 1; }

        if (nIn == 1 && nOut == 2) {
            out1.color = in.color;
            out1.p[0] = *inside[0];
            out1.p[1] = vectorIntersectPlane(p_p, p_n, *inside[0], *outside[0]);
            out1.p[2] = vectorIntersectPlane(p_p, p_n, *inside[0], *outside[1]);
            return 1;
        }

        if (nIn == 2 && nOut == 1) {
            out1.color = out2.color = in.color;
            out1.p[0] = *inside[0]; out1.p[1] = *inside[1];
            out1.p[2] = vectorIntersectPlane(p_p, p_n, *inside[0], *outside[0]);
            out2.p[0] = *inside[1];
            out2.p[1] = out1.p[2];
            out2.p[2] = vectorIntersectPlane(p_p, p_n, *inside[1], *outside[0]);
            return 2;
        }

        return 0;
    }

} // namespace Renderer