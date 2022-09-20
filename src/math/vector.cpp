#include <cstdlib>

#include "vector.h"

//------------------------------------------------------------------------------
//                                 VECTOR2
//------------------------------------------------------------------------------
Bubble::Vec2& Bubble::Vec2::normalize() {
    f32 t = length();
    if (t > 0.0f)
        *this *= 1.0f/t;
    return *this;
}

Bubble::Vec2 Bubble::Vec2::rand() {
    Vec2 v((f32)(::rand()), (f32)(::rand()));
    v -= 0.5f*RAND_MAX;
    return v.normalize();
}

//------------------------------------------------------------------------------
//                                 VECTOR3
//------------------------------------------------------------------------------
f32 Bubble::Vec3::min() const {
    f32 t = x;
    if (y < t)
      t = y;
    if (z < t)
      t = z;
    return t;
}

f32 Bubble::Vec3::max() const {
    f32 t = x;
    if (y > t)
      t = y;
    if (z > t)
      t = z;
    return t;
}

Bubble::Vec3& Bubble::Vec3::normalize() {
    f32 t = length();
    if (t > 0.0f)
      *this *= 1.0f/t;
    return *this;
}   

Bubble::Vec3 Bubble::Vec3::rand() {
    Vec3 v((f32)(::rand()), (f32)(::rand()), (f32)(::rand()));
    v -= 0.5f*RAND_MAX;
    return v.normalize();
}

//------------------------------------------------------------------------------
//                                 VECTOR4
//------------------------------------------------------------------------------
f32 Bubble::Vec4::min() const {
    f32 t = x;
    if (y < t)
      t = y;
    if (z < t)
      t = z;
    if (w < t)
      t = w;
    return t;
}

f32 Bubble::Vec4::max() const {
    f32 t = x;
    if (y > t)
      t = y;
    if (z > t)
      t = z;
    if (w > t)
      t = w;
    return t;
}

Bubble::Vec4& Bubble::Vec4::normalize() {
    f32 t = length();
    if (t > 0.0f)
      *this *= 1.0f/t;
    return *this;
}

Bubble::Vec4 Bubble::Vec4::rand() {
    Vec4 v((f32)(::rand()), (f32)(::rand()), (f32)(::rand()), (f32)(::rand()));
    v -= 0.5f*RAND_MAX;
    return v.normalize();
}