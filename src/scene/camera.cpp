#include <GLFW/glfw3.h>

#include "camera.h"
#include "../window/input.h"

namespace Bubble {

    void Camera::Init(f32 aspect, f32 fov, f32 near, f32 far, const Vec3& position) {
        this->position = position;
        fieldOfView = fov;
        near = near;
        far = far;
        //up = Vec3(0.0f, 1.0f, 0.0f);
        //right = Vec3(1.0f, 0.0f, 0.0f);
        //front = Vec3(0.0f, 0.0f, -1.0f);
        //up = Vec3(0.0f, 1.0f, -1.0f).normalize();
        
        front = -position;
        front = front.normalize();
        pitch = Degrees(asin(front.y));
        yaw = Degrees(asin(front.z/cosf(Radians(pitch))));
        right = (Vec3::cross(front, Vec3(0.0f, 1.0f, 0.0f))).normalize();
        up = (Vec3::cross(right, front)).normalize();
        projection = Perspective(fov, aspect, near, far);
    }

    Mat4 Camera::GetViewMatrix() const {
        //return Math::Mat4(Math::Vec4(right, 0.0f), Math::Vec4(up, 0.0f), Math::Vec4(front, 0.0f), Math::Vec4(position, 1.0f));
        return LookAt(position, position + front, up);
    }

    Mat4 Camera::GetInvViewMatrix() const {
        return (LookAt(position, position + front, up)).inverse();
    }

    void Camera::RecomputeCamera(const Vec3& pos) {
        this->position = pos;
        
        front = -position;
        front = front.normalize();
        pitch = Degrees(asin(front.y));
        yaw = Degrees(asin(front.z/cosf(Radians(pitch))));
        right = (Vec3::cross(front, Vec3(0.0f, 1.0f, 0.0f))).normalize();
        up = (Vec3::cross(right, front)).normalize();
    }

    void Camera::TopView(f32 height) {
        position = Vec3(0.0f, height, 0.0f);
        pitch = -89.9f;

        Vec3 tmpFront;
        tmpFront.x = cosf(Radians(yaw))*cosf(Radians(pitch));
        tmpFront.y = sinf(Radians(pitch));
        tmpFront.z = sinf(Radians(yaw))*cosf(Radians(pitch));

        front = tmpFront.normalize();
        //right = (Vec3::cross(front, Vec3(0.0f, 1.0f, 0.0f))).normalize();
        up = (Vec3::cross(right, front)).normalize(); 
    }

    void Camera::Update(f32 deltaTime) {
        UpdatePosition(deltaTime);
        UpdateVectors();
    }

    void Camera::UpdatePosition(f32 delta) {
        if (Input::GetKey(GLFW_KEY_W)) {
            position += front*delta*speed;
        }
        if (Input::GetKey(GLFW_KEY_S)) {
            position += front*-delta*speed;
        }
        if (Input::GetKey(GLFW_KEY_D)) {
            position += right*delta*speed;
        }
        if (Input::GetKey(GLFW_KEY_A)) {
            position += right*-delta*speed;
        }
        if (Input::GetKey(GLFW_KEY_SPACE)) {
            position += up*delta*speed;
        }
        if (Input::GetKey(GLFW_KEY_LEFT_SHIFT)) {
            position += up*-delta*speed;
        }
    }

    void Camera::UpdateVectors() {
        if (Input::GetMouseButton(RightButton)) {
            Vec2 mouseDelta = Input::GetMouseDelta();
            yaw += (f32)mouseDelta.x*mouseSense;
            pitch += (f32)mouseDelta.y*mouseSense;

            if (pitch > 89.9f) pitch = 89.9f;
            if (pitch < -89.9f) pitch = -89.9f;

            Vec3 tmpFront;
            tmpFront.x = cosf(Radians(yaw))*cosf(Radians(pitch));
            tmpFront.y = sinf(Radians(pitch));
            tmpFront.z = sinf(Radians(yaw))*cosf(Radians(pitch));

            front = tmpFront.normalize();
            right = (Vec3::cross(front, Vec3(0.0f, 1.0f, 0.0f))).normalize();
            up = (Vec3::cross(right, front)).normalize();
        }
    } 
}