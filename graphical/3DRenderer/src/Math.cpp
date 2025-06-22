/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Math
*/

#include "Math.hpp"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

namespace Renderer {

Mat4x4 Mat4x4::makeIdentity() {
    Mat4x4 matrix;
    matrix.m[0][0] = 1.0f; matrix.m[1][1] = 1.0f;
    matrix.m[2][2] = 1.0f; matrix.m[3][3] = 1.0f;
    return matrix;
}

Mat4x4 Mat4x4::makeRotationX(float angleRad) {
    Mat4x4 matrix = makeIdentity();
    matrix.m[1][1] = std::cos(angleRad); matrix.m[1][2] = std::sin(angleRad);
    matrix.m[2][1] = -std::sin(angleRad); matrix.m[2][2] = std::cos(angleRad);
    return matrix;
}

Mat4x4 Mat4x4::makeRotationY(float angleRad) {
    Mat4x4 matrix = makeIdentity();
    matrix.m[0][0] = std::cos(angleRad); matrix.m[0][2] = std::sin(angleRad);
    matrix.m[2][0] = -std::sin(angleRad); matrix.m[2][2] = std::cos(angleRad);
    return matrix;
}

Mat4x4 Mat4x4::makeRotationZ(float angleRad) {
    Mat4x4 matrix = makeIdentity();
    matrix.m[0][0] = std::cos(angleRad); matrix.m[0][1] = std::sin(angleRad);
    matrix.m[1][0] = -std::sin(angleRad); matrix.m[1][1] = std::cos(angleRad);
    return matrix;
}

Mat4x4 Mat4x4::makeScale(float x, float y, float z) {
    Mat4x4 matrix = makeIdentity();
    matrix.m[0][0] = x; matrix.m[1][1] = y; matrix.m[2][2] = z;
    return matrix;
}

Mat4x4 Mat4x4::makeTranslation(float x, float y, float z) {
    Mat4x4 matrix = makeIdentity();
    matrix.m[3][0] = x; matrix.m[3][1] = y; matrix.m[3][2] = z;
    return matrix;
}

Mat4x4 Mat4x4::makeProjection(float fovDeg, float aspectRatio, float near, float far) {
    Mat4x4 matrix;
    float fovRad = 1.0f / std::tan(fovDeg * 0.5f * M_PI / 180.0f);
    matrix.m[0][0] = fovRad / aspectRatio;
    matrix.m[1][1] = fovRad;
    matrix.m[2][2] = far / (far - near);
    matrix.m[3][2] = (-far * near) / (far - near);
    matrix.m[2][3] = 1.0f;
    matrix.m[3][3] = 0.0f;
    return matrix;
}

Renderer::Mat4x4 Renderer::Mat4x4::pointAt(const Vec3& pos, const Vec3& target, const Vec3& up) {
    Vec3 newForward = { target.x - pos.x, target.y - pos.y, target.z - pos.z };
    float l_f = std::sqrt(newForward.x*newForward.x + newForward.y*newForward.y + newForward.z*newForward.z);
    if (l_f > 0.0f) {
        newForward.x /= l_f; newForward.y /= l_f; newForward.z /= l_f;
    }
    float dp = newForward.x*up.x + newForward.y*up.y + newForward.z*up.z;
    Vec3 a = { newForward.x*dp, newForward.y*dp, newForward.z*dp };
    Vec3 newUp = { up.x - a.x, up.y - a.y, up.z - a.z };
    float l_u = std::sqrt(newUp.x*newUp.x + newUp.y*newUp.y + newUp.z*newUp.z);
    if (l_u > 0.0f) {
        newUp.x /= l_u; newUp.y /= l_u; newUp.z /= l_u;
    }
    Vec3 newRight = {
        newUp.y*newForward.z - newUp.z*newForward.y,
        newUp.z*newForward.x - newUp.x*newForward.z,
        newUp.x*newForward.y - newUp.y*newForward.x
    };
    Mat4x4 m;
    m.m[0][0]=newRight.x;   m.m[0][1]=newRight.y;   m.m[0][2]=newRight.z;   m.m[0][3]=0.0f;
    m.m[1][0]=newUp.x;      m.m[1][1]=newUp.y;      m.m[1][2]=newUp.z;      m.m[1][3]=0.0f;
    m.m[2][0]=newForward.x; m.m[2][1]=newForward.y; m.m[2][2]=newForward.z; m.m[2][3]=0.0f;
    m.m[3][0]=pos.x;        m.m[3][1]=pos.y;        m.m[3][2]=pos.z;        m.m[3][3]=1.0f;
    return m;
}

    Renderer::Mat4x4 Renderer::Mat4x4::quickInverse(const Mat4x4& mat) {
    Mat4x4 m;

    m.m[0][0] = mat.m[0][0]; m.m[0][1] = mat.m[1][0]; m.m[0][2] = mat.m[2][0]; m.m[0][3] = 0.0f;
    m.m[1][0] = mat.m[0][1]; m.m[1][1] = mat.m[1][1]; m.m[1][2] = mat.m[2][1]; m.m[1][3] = 0.0f;
    m.m[2][0] = mat.m[0][2]; m.m[2][1] = mat.m[1][2]; m.m[2][2] = mat.m[2][2]; m.m[2][3] = 0.0f;

    m.m[3][0] = -(mat.m[3][0]*m.m[0][0] + mat.m[3][1]*m.m[1][0] + mat.m[3][2]*m.m[2][0]);
    m.m[3][1] = -(mat.m[3][0]*m.m[0][1] + mat.m[3][1]*m.m[1][1] + mat.m[3][2]*m.m[2][1]);
    m.m[3][2] = -(mat.m[3][0]*m.m[0][2] + mat.m[3][1]*m.m[1][2] + mat.m[3][2]*m.m[2][2]);
    m.m[3][3] = 1.0f;
    return m;
}

Vec4 multiplyMatrixVector(const Vec4& i, const Mat4x4& m) {
    return Vec4{
        i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0],
        i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1],
        i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2],
        i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3]
    };
}

Mat4x4 multiplyMatrixMatrix(const Mat4x4& a, const Mat4x4& b) {
    Mat4x4 matrix;
    for (int c = 0; c < 4; ++c)
        for (int r = 0; r < 4; ++r)
            matrix.m[r][c] = a.m[r][0] * b.m[0][c] + a.m[r][1] * b.m[1][c] + a.m[r][2] * b.m[2][c] + a.m[r][3] * b.m[3][c];
    return matrix;
}

float getRandomAngle() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dist(0.0f, 360.0f);
    return dist(gen);
}

} // namespace Renderer