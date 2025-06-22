// include/Math.hpp
#pragma once
#include <cmath>
#include <random>

namespace Renderer {
    struct Vec3 {
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
    };

    struct Vec4 {
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
        float w = 1.f;
    };

    struct Mat4x4 {
        float m[4][4] = {};

        // Construction de matrices
        static Mat4x4 makeIdentity();
        static Mat4x4 makeRotationX(float angleRad);
        static Mat4x4 makeRotationY(float angleRad);
        static Mat4x4 makeRotationZ(float angleRad);
        static Mat4x4 makeScale(float x, float y, float z);
        static Mat4x4 makeTranslation(float x, float y, float z);
        static Mat4x4 makeProjection(float fovDeg, float aspectRatio, float near, float far);

        // Fonctions utilitaires
        static Mat4x4 pointAt(const Vec3& pos, const Vec3& target, const Vec3& up);
        static Mat4x4 quickInverse(const Mat4x4& m);
    };

    // Multiplications
    Vec4 multiplyMatrixVector(const Vec4& i, const Mat4x4& m);
    Mat4x4 multiplyMatrixMatrix(const Mat4x4& a, const Mat4x4& b);
    float getRandomAngle();
}
