#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "matrix.h"

namespace Bubble {
    inline f32 Radians(f32 angle) { return (f32)((angle*M_PI)/180.0f); }
    inline f32 Degrees(f32 angle) { return (f32)((angle*180.0f)/M_PI); }

    inline Mat4 TranslationMatrix(const Vec3& translate) {
        Mat4 mat;
        mat[3] = Vec4(translate, 1.0f);
        return mat;
    }

    inline Mat4 ScaleMatrix(const Vec3& scale) {
        Mat4 mat;
        mat[0][0] = scale.x;
        mat[1][1] = scale.y;
        mat[2][2] = scale.z;
        return mat;
    }

    inline Mat4 RotationMatrixX(f32 angle) {
        f32 cos = cosf(Radians(angle));
        f32 sin = sinf(Radians(angle));
        return Mat4({1.0f, 0.0f,  0.0f, 0.0f}, {0.0f, cos, -sin, 0.0f}, {0.0f, sin, cos, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        //return Mat4({1.0f, 0.0f,  0.0f, 0.0f}, {0.0f, cos, sin, 0.0f}, {0.0f, -sin, cos, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
    }

    inline Mat4 RotationMatrixY(f32 angle) {
        f32 cos = cosf(Radians(angle));
        f32 sin = sinf(Radians(angle));
        return Mat4({cos, 0.0f,  sin, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {-sin, 0.0f, cos, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        //return Mat4({cos, 0.0f,  -sin, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {sin, 0.0f, cos, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
    }

    inline Mat4 RotationMatrixZ(f32 angle) {
        f32 cos = cosf(Radians(angle));
        f32 sin = sinf(Radians(angle));
        return Mat4({cos, -sin,  0.0f, 0.0f}, {sin, cos, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        //return Mat4({cos, sin,  0.0f, 0.0f}, {-sin, cos, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
    }

    inline Mat4 RotationMatrix(f32 angleX, f32 angleY, f32 angleZ) {
        return RotationMatrixZ(angleZ)*RotationMatrixY(angleY)*RotationMatrixX(angleX);
        //return RotationMatrixX(angleX)*RotationMatrixY(angleY)*RotationMatrixZ(angleZ);
    }

    inline Mat4 RotationMatrix(const Vec3& v) {
        return RotationMatrixZ(v.z)*RotationMatrixY(v.y)*RotationMatrixX(v.x);
        //return RotationMatrixZ(v.x)*RotationMatrixY(v.y)*RotationMatrixX(v.z);
    }

    inline Mat4 Perspective(f32 fov, f32 aspect, f32 near, f32 far) {
        Mat4 m;
        m[0][0] = 1.0f/(aspect*tanf(Radians(fov)*0.5f));
        m[1][1] = 1.0f/(tanf(Radians(fov)*0.5f));
        m[2][2] = -(far + near)/(far - near);
        m[3][3] = 0.0f;
        m[3][2] = -(2.0f*far*near)/(far - near);
        m[2][3] = -1.0f;
        return m;
    }

    inline Mat4 Orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
        Mat4 m;
        m[0][0] = 2.0f/(right - left);
        m[1][1] = 2.0f/(top - bottom);
        m[2][2] = -2.0f/(far - near);
        m[3][0] = -(right + left)/(right - left);
        m[3][1] = -(top + bottom)/(top - bottom);
        m[3][2] = -(far + near)/(far - near);
        return m;
    }

    inline Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
        Mat4 m;
        Vec3 x, y, z;

        z = eye - center;
        z = z.normalize();
        y = up;
        x = Vec3::cross(y, z);
        y = Vec3::cross(z, x);
        x = x.normalize();
        y = y.normalize();

        m[0][0] = x.x;
        m[1][0] = x.y;
        m[2][0] = x.z;
        m[3][0] = -Vec3::dot(x, eye);
        m[0][1] = y.x;
        m[1][1] = y.y;
        m[2][1] = y.z;
        m[3][1] = -Vec3::dot(y, eye);
        m[0][2] = z.x;
        m[1][2] = z.y;
        m[2][2] = z.z;
        m[3][2] = -Vec3::dot(z, eye);
        m[0][3] = 0;
        m[1][3] = 0;
        m[2][3] = 0;
        m[3][3] = 1.0f;

        return m;
    } 

    inline f32 Sign(f32 value) {
        return (f32)((0.0f < value) - (value < 0.0f));
    }

    inline f32 Abs(f32 value) {
        return value*((value > 0.0f) - (value < 0.0f));
    }

    inline f32 Clamp(f32 value, f32 min, f32 max) {
        const f32 t = fmaxf(min, value); 
        return fminf(t, max);
    }

    inline Vec2 GetClosestPointOnLineSegment(Vec2 a, Vec2 b, Vec2 p) {
        Vec2 ap = p - a;  
        Vec2 ab = b - a;  

        f32 magnitudeAB = ab.length();      
        f32 ABAPproduct = Vec2::dot(ap, ab);     
        f32 t = ABAPproduct/magnitudeAB;

        if (t < 0.0f) return a;
        else if (t > magnitudeAB) return b;
        else return a + ab/magnitudeAB*t;
    }

}

#endif