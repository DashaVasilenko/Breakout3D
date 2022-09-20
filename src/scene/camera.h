#ifndef CAMERA_H
#define CAMERA_H

#include "../math/matrix.h"
#include "../math/functions.h"

namespace Bubble {

    class Camera {
    public:
        //Camera() {}
        void Init(f32 aspect, f32 fov = 45.0f, f32 near = 0.1f, f32 far = 100.0f, const Vec3& position = Vec3(0.0f, 0.0f, 3.0f));
        void Update(f32 deltaTime);

        inline Mat4 GetProjectionMatrix() const { return projection; }
        Mat4 GetViewMatrix() const;
        Mat4 GetInvViewMatrix() const;
        inline Vec3 GetPosition() const { return position; }
        inline Vec3 GetForward() const { return front; }
        inline Vec3 GetRight() const { return right; }
        inline Vec3 GetUp() const { return up; }
        inline f32 GetFieldOfView() const { return fieldOfView; }

        inline void SetProjection(f32 aspect) { projection = Perspective(fieldOfView, aspect, near, far); }
        inline void SetPosition(const Vec3& pos) { position = pos; }
        void RecomputeCamera(const Vec3& pos); // recompute camera position and vectors such that camera looks at the (0, 0, 0)
        void TopView(f32 height);

    private:
        Mat4 projection;

        // camera vectors and position
        Vec3 up;
        Vec3 right;
        Vec3 front;
        Vec3 position;
        Vec2 lastMousePosition;

        // camera angles
        f32 pitch = 0.0f;
        f32 yaw = -90.0f;
        f32 fieldOfView = 90.0f;
        f32 near = 0.1f; 
        f32 far = 100.0f;
    
        f32 speed = 5.5f;
        f32 mouseSense = 0.5f;

        void UpdatePosition(f32 deltaTime);
        void UpdateVectors();
    };

}

#endif /* End of CAMERA_H */