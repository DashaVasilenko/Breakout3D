#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>

#include "vector.h"

//#define PI 3.14159265358979323846  /* pi */

namespace Bubble {
    //------------------------------------------------------------------------------
    //                                 MATRIX3x3
    //------------------------------------------------------------------------------
    class Mat3 {
    public:
        Mat3();
        Mat3(const f32* d);
        Mat3(const Vec3& v1, const Vec3& v2, const Vec3& v3);
        //Mat3(const Mat3& m);

        inline bool operator==(const Mat3& m) const { return data[0] == m.data[0] && data[1] == m.data[1] && data[2] == m.data[2]; }
        inline bool operator!=(const Mat3& m) const { return data[0] != m.data[0] || data[1] != m.data[1] || data[2] != m.data[2]; }

        inline Vec3& operator[](i32 i) { assert(i >= 0 && i < 3); return data[i]; }
        inline const Vec3& operator[](i32 i) const { assert(i >= 0 && i < 3); return data[i]; }

        inline const f32* GetData() const { return (const f32*)data; }
        inline f32* GetData() { return (f32*)data; }

        inline Mat3& operator=(f32 d) { data[0] = data[1] = data[2] = d; return *this; }
        inline Mat3& operator+=(f32 d) { data[0] += d; data[1] += d; data[2] += d; return *this; }
        inline Mat3& operator-=(f32 d) { data[0] -= d; data[1] -= d; data[2] -= d; return *this; }
        inline Mat3& operator*=(f32 d) { data[0] *= d; data[1] *= d; data[2] *= d; return *this; }
        inline Mat3& operator/=(f32 d) { data[0] /= d; data[1] /= d; data[2] /= d; return *this; }
        inline Mat3& operator=(const Mat3& m) { data[0] = m.data[0]; data[1] = m.data[1]; data[2] = m.data[2]; return *this; }
        inline Mat3& operator+=(const Mat3& m) { data[0] += m.data[0]; data[1] += m.data[1]; data[2] += m.data[2]; return *this; }
        inline Mat3& operator-=(const Mat3& m) { data[0] -= m.data[0]; data[1] -= m.data[1]; data[2] -= m.data[2]; return *this; }
        inline Mat3& operator*=(const Mat3& m) {
            Mat3 res;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++)
                {
                    f32 t = 0.0f;
                    for(int k = 0; k < 3; k++)
                        t += (*this)[k][i]*m[j][k];
                    res[i][j] = t;
                }  
            }
            *this = res;
            return *this;
        }
        inline Mat3& operator/=(const Mat3& m) { data[0] /= m.data[0]; data[1] /= m.data[1]; data[2] /= m.data[2]; return *this; }

        inline Mat3 operator+() const { return Mat3(data[0], data[1], data[2]); }
        inline Mat3 operator-() const { return Mat3(-data[0], -data[1], -data[2]); }
        inline Mat3 operator+(f32 d) const { return Mat3(data[0] + d, data[1] + d, data[2] + d); }
        inline Mat3 operator-(f32 d) const { return Mat3(data[0] - d, data[1] - d, data[2] - d); }
        inline Mat3 operator*(f32 d) const { return Mat3(data[0] * d, data[1] * d, data[2] * d); }
        inline Mat3 operator/(f32 d) const { return Mat3(data[0] / d, data[1] / d, data[2] / d); }
        //inline Vec3 operator*(const Vec3& v) const { return Vec3(Vec3::dot(data[0], v), Vec3::dot(data[1], v), Vec3::dot(data[2], v)); }
        inline Vec3 operator*(const Vec3& v) const { 
            Vec3 v1 = Vec3(data[0].x, data[1].x, data[2].x);
            Vec3 v2 = Vec3(data[0].y, data[1].y, data[2].y);
            Vec3 v3 = Vec3(data[0].z, data[1].z, data[2].z);
            return Vec3(Vec3::dot(v1, v), Vec3::dot(v2, v), Vec3::dot(v3, v)); 
        }
        friend inline Mat3 operator+(f32 d, const Mat3& m) { return Mat3(m.data[0] + d, m.data[1] + d, m.data[2] + d); }
        friend inline Mat3 operator-(f32 d, const Mat3& m) { return Mat3(m.data[0] - d, m.data[1] - d, m.data[2] - d); }
        friend inline Mat3 operator*(f32 d, const Mat3& m) { return Mat3(m.data[0] * d, m.data[1] * d, m.data[2] * d); }
        friend inline Mat3 operator/(f32 d, const Mat3& m) { return Mat3(m.data[0] / d, m.data[1] / d, m.data[2] / d); }
        inline Mat3 operator+(const Mat3& m) const { return Mat3(data[0] + m.data[0], data[1] + m.data[1], data[2] + m.data[2]); }
        inline Mat3 operator-(const Mat3& m) const { return Mat3(data[0] - m.data[0], data[1] - m.data[1], data[2] - m.data[2]); }
        inline Mat3 operator*(const Mat3& m) const { 
            Mat3 res;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++)
                {
                    f32 t = 0.0f;
                    for(int k = 0; k < 3; k++)
                        t += (*this)[k][i]*m[j][k];
                    res[j][i] = t;
                }  
            }
            return res;
        }
        inline Mat3 operator/(const Mat3& m) const { return Mat3(data[0] / m.data[0], data[1] / m.data[1], data[2] / m.data[2]); }

        inline Mat3 transpose() {
            Vec3 v1(data[0].x, data[1].x, data[2].x);
            Vec3 v2(data[0].y, data[1].y, data[2].y);
            Vec3 v3(data[0].z, data[1].z, data[2].z);
            return Mat3(v1, v2, v3); 
        }
        inline f32 determinante() { return data[0][0]*(data[1][1]*data[2][2] - data[2][1]*data[1][2]) +
                                           data[0][1]*(data[1][2]*data[2][0] - data[1][0]*data[2][2]) +
                                           data[0][2]*(data[1][0]*data[2][1] - data[1][1]*data[2][0]);
        }
        Mat3 inverse();
    
    private:
        Vec3 data[3];
    };

    //------------------------------------------------------------------------------
    //                                 MATRIX4x4
    //------------------------------------------------------------------------------
    class Mat4 {
    public:
        Mat4();
        Mat4(const f32* d);
        Mat4(const Vec4& v1, const Vec4& v2, const Vec4& v3, const Vec4& v4);
        //Mat4(const Mat4& m);

        inline bool operator==(const Mat4& m) const { return data[0] == m.data[0] && data[1] == m.data[1] && data[2] == m.data[2] && data[3] == m.data[3]; }
        inline bool operator!=(const Mat4& m) const { return data[0] != m.data[0] || data[1] != m.data[1] || data[2] != m.data[2] || data[3] != m.data[3]; }

        inline Vec4& operator[](i32 i) { assert(i >= 0 && i < 4); return data[i]; }
        inline const Vec4& operator[](i32 i) const { assert(i >= 0 && i < 4); return data[i]; }

        inline const f32* GetData() const { return (const f32*)data; }
        inline f32* GetData() { return (f32*)data; }

        inline Mat4& operator=(f32 d) { data[0] = data[1] = data[2] = data[3] = d; return *this; }
        inline Mat4& operator+=(f32 d) { data[0] += d; data[1] += d; data[2] += d; data[3] += d; return *this; }
        inline Mat4& operator-=(f32 d) { data[0] -= d; data[1] -= d; data[2] -= d; data[3] -= d; return *this; }
        inline Mat4& operator*=(f32 d) { data[0] *= d; data[1] *= d; data[2] *= d; data[3] *= d; return *this; }
        inline Mat4& operator/=(f32 d) { data[0] /= d; data[1] /= d; data[2] /= d; data[3] /= d; return *this; }
        inline Mat4& operator=(const Mat4& m) { data[0] = m.data[0]; data[1] = m.data[1]; data[2] = m.data[2]; data[3] = m.data[3]; return *this; }
        inline Mat4& operator+=(const Mat4& m) { data[0] += m.data[0]; data[1] += m.data[1]; data[2] += m.data[2]; data[3] += m.data[3]; return *this; }
        inline Mat4& operator-=(const Mat4& m) { data[0] -= m.data[0]; data[1] -= m.data[1]; data[2] -= m.data[2]; data[3] -= m.data[3]; return *this; }
        inline Mat4& operator*=(const Mat4& m) {
            Mat4 res;
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++)
                {
                    f32 t = 0.0f;
                    for(int k = 0; k < 4; k++)
                        t += (*this)[k][i]*m[j][k];
                    res[i][j] = t;
                }  
            }
            *this = res;
            return *this;
        }
        inline Mat4& operator/=(const Mat4& m) { data[0] /= m.data[0]; data[1] /= m.data[1]; data[2] /= m.data[2]; data[3] /= m.data[3]; return *this; }

        inline Mat4 operator+() const { return Mat4(data[0], data[1], data[2], data[3]); }
        inline Mat4 operator-() const { return Mat4(-data[0], -data[1], -data[2], -data[3]); }
        inline Mat4 operator+(f32 d) const { return Mat4(data[0] + d, data[1] + d, data[2] + d, data[3] + d); }
        inline Mat4 operator-(f32 d) const { return Mat4(data[0] - d, data[1] - d, data[2] - d, data[3] - d); }
        inline Mat4 operator*(f32 d) const { return Mat4(data[0] * d, data[1] * d, data[2] * d, data[3] * d); }
        inline Mat4 operator/(f32 d) const { return Mat4(data[0] / d, data[1] / d, data[2] / d, data[3] / d); }
        //inline Vec4 operator*(const Vec4& v) const { return Vec4(Vec4::dot(data[0], v), Vec4::dot(data[1], v), Vec4::dot(data[2], v), Vec4::dot(data[3], v)); }
        inline Vec4 operator*(const Vec4& v) const { 
            Vec4 v1 = Vec4(data[0].x, data[1].x, data[2].x, data[3].x);
            Vec4 v2 = Vec4(data[0].y, data[1].y, data[2].y, data[3].y);
            Vec4 v3 = Vec4(data[0].z, data[1].z, data[2].z, data[3].z);
            Vec4 v4 = Vec4(data[0].w, data[1].w, data[2].w, data[3].w);
            return Vec4(Vec4::dot(v1, v), Vec4::dot(v2, v), Vec4::dot(v3, v), Vec4::dot(v4, v)); 
        }
        friend inline Mat4 operator+(f32 d, const Mat4& m) { return Mat4(m.data[0] + d, m.data[1] + d, m.data[2] + d, m.data[3] + d); }
        friend inline Mat4 operator-(f32 d, const Mat4& m) { return Mat4(m.data[0] - d, m.data[1] - d, m.data[2] - d, m.data[3] - d); }
        friend inline Mat4 operator*(f32 d, const Mat4& m) { return Mat4(m.data[0] * d, m.data[1] * d, m.data[2] * d, m.data[3] * d); }
        friend inline Mat4 operator/(f32 d, const Mat4& m) { return Mat4(m.data[0] / d, m.data[1] / d, m.data[2] / d, m.data[3] / d); }
        inline Mat4 operator+(const Mat4& m) const { return Mat4(data[0] + m.data[0], data[1] + m.data[1], data[2] + m.data[2], data[3] + m.data[3]); }
        inline Mat4 operator-(const Mat4& m) const { return Mat4(data[0] - m.data[0], data[1] - m.data[1], data[2] - m.data[2], data[3] - m.data[3]); }
        inline Mat4 operator*(const Mat4& m) const { 
            Mat4 res;
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++)
                {
                    f32 t = 0.0f;
                    for(int k = 0; k < 4; k++)
                        t += (*this)[k][i]*m[j][k];
                    res[j][i] = t;
                }  
            }
            return res;
        }
        inline Mat4 operator/(const Mat4& m) const { return Mat4(data[0] / m.data[0], data[1] / m.data[1], data[2] / m.data[2], data[3] + m.data[3]); }

        inline Mat4 transpose() {
            Vec4 v1(data[0].x, data[1].x, data[2].x, data[3].x);
            Vec4 v2(data[0].y, data[1].y, data[2].y, data[3].y);
            Vec4 v3(data[0].z, data[1].z, data[2].z, data[3].z);
            Vec4 v4(data[0].w, data[1].w, data[2].w, data[3].w);
            return Mat4(v1, v2, v3, v4); 
        }
        f32 determinante();
        Mat4 inverse();
    
    private:
        Vec4 data[4];
    };
}

#endif