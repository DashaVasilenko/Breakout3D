#include <string.h>

#include "input.h"

namespace Bubble{
    bool Input::keys[512] = {false};
    bool Input::previousKeys[512] = {false};
    bool Input::mouse[8] = {false};
    bool Input::previousMouse[8] = {false};
    Vec2 Input::mousePosition = Vec2(0.0f);
    Vec2 Input::previousMousePosition = Vec2(0.0f);
    Vec2 Input::mouseDelta = Vec2(0.0f);
    bool Input::firstMouseMove = true;

    void Input::Update(GLFWwindow* window) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if (firstMouseMove) {
            firstMouseMove = false;
            mousePosition = Vec2((float)xpos, (float)ypos);
            return;
        }

        memcpy(previousKeys, keys, sizeof(bool)*512);
        memcpy(previousMouse, mouse, sizeof(bool)*8);
        previousMousePosition = mousePosition;
        mousePosition = Vec2((float)xpos, (float)ypos);
        mouseDelta = mousePosition - previousMousePosition;
        mouseDelta.y *= -1.0f;

    }
}