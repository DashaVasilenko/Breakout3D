#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mesh.h"
#include "../math/matrix.h"
#include "../math/functions.h"

namespace Bubble {

    class Transform {
    public:
        Transform(Vec3 r = Vec3(0.0f), Vec3 p = Vec3(0.0f), Vec3 s = Vec3(1.0f)): rotation(r), position(p), scale(s) { }

        inline void SetRotation(f32 x, f32 y, f32 z) { rotation = Vec3(x, y, z); }
        inline void SetPosition(Vec3 p) { position = p; }
        inline void SetPosition(f32 x, f32 y, f32 z) { position = Vec3(x, y, z); }
        inline void SetScale(f32 x, f32 y, f32 z) { scale = Vec3(x, y, z); }

        inline Vec3 GetRotation() const { return rotation; }
        inline Vec3 GetPosition() const { return position; }
        inline Vec3 GetForward() const {  Vec4 v = GetModelMatrix()*Vec4(0.0f, 0.0f, -1.0f, 0.0f); return Vec3(v.x, v.y, v.z).normalize(); }
        inline Vec3 GetUp() const {  Vec4 v = GetModelMatrix()*Vec4(0.0f, 1.0f, 0.0f, 0.0f); return Vec3(v.x, v.y, v.z).normalize(); }
        inline Vec3 GetRight() const {  Vec4 v = GetModelMatrix()*Vec4(1.0f, 0.0f, 0.0f, 0.0f); return Vec3(v.x, v.y, v.z).normalize(); }
        inline Vec3 GetScale() const { return scale; }
        inline Mat4 GetModelMatrix() const { return TranslationMatrix(position)*RotationMatrix(rotation)*ScaleMatrix(scale); }

        inline void Rotate(f32 x, f32 y, f32 z) { rotation += Vec3(x, y, z); }

    private:
        Vec3 rotation; // euler angles in degrees
        Vec3 position;
        Vec3 scale;

    };
}

#endif /* End of TRANSFORM_H */