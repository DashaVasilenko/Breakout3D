#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>
#include <cmath>

#include "../core/types.h"

namespace Bubble {
    //------------------------------------------------------------------------------
    //                                 VECTOR2
    //------------------------------------------------------------------------------
    class Vec2 {
    public:
        f32 x, y;

        Vec2(): x(0.0f), y(0.0f) { }
        Vec2(f32 d): x(d), y(d) { }
        Vec2(f32 dx, f32 dy): x(dx), y(dy) { }
        //Vec2(const Vec2& v) { x = v.x; y = v.y; }

        inline bool operator==(const Vec2& v) const { return x == v.x && y == v.y; }
        inline bool operator!=(const Vec2& v) const { return x != v.x || y != v.y; }

        inline f32 operator[](int i) const { assert(i >= 0 && i < 2); return (&x)[i]; }
        inline f32& operator[](int i) { assert(i >= 0 && i < 2); return (&x)[i]; }

        inline Vec2& operator=(f32 d) { x = y = d; return *this; }
        inline Vec2& operator+=(f32 d) { x += d; y += d; return *this; }
        inline Vec2& operator-=(f32 d) { x -= d; y -= d; return *this; }
        inline Vec2& operator*=(f32 d) { x *= d; y *= d; return *this; }
        inline Vec2& operator/=(f32 d) { x /= d; y /= d; return *this; }
        inline Vec2& operator=(const Vec2& v) { x = v.x; y = v.y; return *this; }
        inline Vec2& operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
        inline Vec2& operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }
        inline Vec2& operator*=(const Vec2& v) { x *= v.x; y *= v.y; return *this; }
        inline Vec2& operator/=(const Vec2& v) { x /= v.x; y /= v.y; return *this; }

        inline Vec2 operator+() const { return Vec2(x, y); }
        inline Vec2 operator-() const { return Vec2(-x, -y); }
        inline Vec2 operator+(f32 d) const { return Vec2(x + d, y + d); }
        inline Vec2 operator-(f32 d) const { return Vec2(x - d, y - d); }
        inline Vec2 operator*(f32 d) const { return Vec2(x * d, y * d); }
        inline Vec2 operator/(f32 d) const { return Vec2(x / d, y / d); }
        inline Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
        inline Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
        inline Vec2 operator*(const Vec2& v) const { return Vec2(x * v.x, y * v.y); }
        inline Vec2 operator/(const Vec2& v) const { return Vec2(x / v.x, y / v.y); }

        f32 min() const { return x < y ? x : y; } 
        f32 max() const { return x > y ? x : y; }
        inline f32 sum() const { return x + y; }
        inline f32 length() const { return sqrt(x*x + y*y); }
        Vec2& normalize();

        inline static f32 distance(const Vec2& v1, const Vec2& v2) { return (v1 - v2).length(); }
        inline static f32 dot(const Vec2& v1, const Vec2& v2) { return v1.x*v2.x + v1.y*v2.y; }
        inline static f32 dot2(const Vec2& v) { return v.x*v.x + v.y*v.y; }
        inline static Vec2 abs(const Vec2& v) { return Vec2(fabs(v.x), fabs(v.y)); }
        inline static Vec2 pow(const Vec2& v, f32 t) { return Vec2(::pow(v.x, t), ::pow(v.y, t)); }
        static Vec2 rand();
    };  

    //------------------------------------------------------------------------------
    //                                 VECTOR3
    //------------------------------------------------------------------------------
    class Vec3 {
    public:
        f32 x, y, z;

        Vec3(): x(0.0f), y(0.0f), z(0.0f) { }
        Vec3(f32 d): x(d), y(d), z(d) { }
        Vec3(f32 dx, f32 dy, f32 dz): x(dx), y(dy), z(dz) { }
        //Vec3(const Vec3& v) { x = v.x; y = v.y; z = v.z; }

        inline bool operator==(const Vec3& v) const { return x == v.x && y == v.y && z == v.z; }
        inline bool operator!=(const Vec3& v) const { return x != v.x || y != v.y || z != v.z; }

        inline f32 operator[](int i) const { assert(i >= 0 && i < 3); return (&x)[i]; }
        inline f32& operator[](int i) { assert(i >= 0 && i < 3); return (&x)[i]; }

        inline Vec3& operator=(f32 d) { x = y = z = d; return *this; }
        inline Vec3& operator+=(f32 d) { x += d; y += d; z += d; return *this; }
        inline Vec3& operator-=(f32 d) { x -= d; y -= d; z -= d; return *this; }
        inline Vec3& operator*=(f32 d) { x *= d; y *= d; z *= d; return *this; }
        inline Vec3& operator/=(f32 d) { x /= d; y /= d; z /= d; return *this; }
        inline Vec3& operator=(const Vec3& v) { x = v.x; y = v.y; z = v.z; return *this; }
        inline Vec3& operator+=(const Vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
        inline Vec3& operator-=(const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
        inline Vec3& operator*=(const Vec3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
        inline Vec3& operator/=(const Vec3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

        inline Vec3 operator+() const { return Vec3(x, y, z); }
        inline Vec3 operator-() const { return Vec3(-x, -y, -z); }
        inline Vec3 operator+(f32 d) const { return Vec3(x + d, y + d, z + d); }
        inline Vec3 operator-(f32 d) const { return Vec3(x - d, y - d, z - d); }
        inline Vec3 operator*(f32 d) const { return Vec3(x * d, y * d, z * d); }
        inline Vec3 operator/(f32 d) const { return Vec3(x / d, y / d, z / d); }
        inline Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
        inline Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
        inline Vec3 operator*(const Vec3& v) const { return Vec3(x * v.x, y * v.y, z * v.z); }
        inline Vec3 operator/(const Vec3& v) const { return Vec3(x / v.x, y / v.y, z / v.z); }

        f32 min() const;
        f32 max() const;
        inline f32 sum() const { return x + y + z; }
        inline f32 length() const { return sqrt(x*x + y*y + z*z); }
        Vec3& normalize();

        inline static f32 distance(const Vec3& v1, const Vec3& v2) { return (v1 - v2).length(); }
        inline static f32 dot(const Vec3& v1, const Vec3& v2) { return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z; }
        inline static f32 dot2(const Vec3& v) { return v.x*v.x + v.y*v.y + v.z*v.z; }
        inline static Vec3 cross(const Vec3& v1, const Vec3& v2) { return Vec3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x); }
        inline static Vec3 abs(const Vec3& v) { return Vec3(fabs(v.x), fabs(v.y), fabs(v.z)); }
        inline static Vec3 pow(const Vec3& v, f32 t) { return Vec3(::pow(v.x, t), ::pow(v.y, t), ::pow(v.z, t)); }
        static Vec3 rand();
    };

    //------------------------------------------------------------------------------
    //                                 VECTOR4
    //------------------------------------------------------------------------------
    class Vec4 {
    public:
        f32 x, y, z, w;

        Vec4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
        Vec4(f32 d): x(d), y(d), z(d), w(d) { }
        Vec4(f32 dx, f32 dy, f32 dz, f32 dw): x(dx), y(dy), z(dz), w(dw) { }
        Vec4(Vec3 v, f32 d): x(v.x), y(v.y), z(v.z), w(d) { }
        //Vec4(const Vec4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }

        inline bool operator==(const Vec4& v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
        inline bool operator!=(const Vec4& v) const { return x != v.x || y != v.y || z != v.z || w != v.w; }

        inline f32 operator[](int i) const { assert(i >= 0 && i < 4); return (&x)[i]; }
        inline f32& operator[](int i) { assert(i >= 0 && i < 4); return (&x)[i]; }

        inline Vec4& operator=(f32 d) { x = y = z = w = d; return *this; }
        inline Vec4& operator+=(f32 d) { x += d; y += d; z += d; w += d; return *this; }
        inline Vec4& operator-=(f32 d) { x -= d; y -= d; z -= d; w -= d; return *this; }
        inline Vec4& operator*=(f32 d) { x *= d; y *= d; z *= d; w *= d; return *this; }
        inline Vec4& operator/=(f32 d) { x /= d; y /= d; z /= d; w /= d; return *this; }
        inline Vec4& operator=(const Vec4& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
        inline Vec4& operator+=(const Vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
        inline Vec4& operator-=(const Vec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
        inline Vec4& operator*=(const Vec4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
        inline Vec4& operator/=(const Vec4& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

        inline Vec4 operator+() const { return Vec4(x, y, z, w); }
        inline Vec4 operator-() const { return Vec4(-x, -y, -z, -w); }
        inline Vec4 operator+(f32 d) const { return Vec4(x + d, y + d, z + d, w + d); }
        inline Vec4 operator-(f32 d) const { return Vec4(x - d, y - d, z - d, w - d); }
        inline Vec4 operator*(f32 d) const { return Vec4(x * d, y * d, z * d, w * d); }
        inline Vec4 operator/(f32 d) const { return Vec4(x / d, y / d, z / d, w / d); }
        inline Vec4 operator+(const Vec4& v) const { return Vec4(x + v.x, y + v.y, z + v.z, w + v.w); }
        inline Vec4 operator-(const Vec4& v) const { return Vec4(x - v.x, y - v.y, z - v.z, w - v.w); }
        inline Vec4 operator*(const Vec4& v) const { return Vec4(x * v.x, y * v.y, z * v.z, w * v.w); }
        inline Vec4 operator/(const Vec4& v) const { return Vec4(x / v.x, y / v.y, z / v.z, w / v.w); }

        f32 min() const;
        f32 max() const;
        inline f32 sum() const { return x + y + z + w; }
        inline f32 length() const { return sqrt(x*x + y*y + z*z + w*w); }
        Vec4& normalize();

        inline static f32 distance(const Vec4& v1, const Vec4& v2) { return (v1 - v2).length(); }
        inline static f32 dot(const Vec4& v1, const Vec4& v2) { return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w; }
        inline static f32 dot2(const Vec4& v) { return v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w; }
        inline static Vec4 abs(const Vec4& v) { return Vec4(fabs(v.x), fabs(v.y), fabs(v.z), fabs(v.w)); }
        inline static Vec4 pow(const Vec4& v, f32 t) { return Vec4(::pow(v.x, t), ::pow(v.y, t), ::pow(v.z, t), ::pow(v.w, t)); }
        static Vec4 rand();
    };
}

#endif