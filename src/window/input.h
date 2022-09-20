#ifndef INPUT_H
#define INPUT_H

#include <cstdio>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../math/vector.h"

namespace Bubble {

    enum MouseButton {
        LeftButton = 0,    
        RightButton = 1,
        MiddleButton = 2,
        Button4 = 3,
        Button5 = 4,
        Button6 = 5,
        Button7 = 6,
        Button8 = 7
    };

    enum Key {
        Space = 32,
        Escape = 256,
        Enter = 257,
        LeftShift = 340,

        Key1 = 49,
        Key2 = 50,
        Key3 = 51,
        Key4 = 52,

        RightArrow = 262,
        LeftArrow = 263,
        DownArrow = 264,
        UpArrow = 265,

        W = 87,
        A = 65,
        S = 83,
        D = 68,
        Q = 81,
        E = 69,
    };

    class Input {
        friend class Window;
    public:
        inline static bool GetKey(i32 keyCode) { return keys[keyCode]; }
        inline static bool GetKeyDown(i32 keyCode) { return keys[keyCode] && !previousKeys[keyCode]; }
        inline static bool GetKeyUp(i32 keyCode) { return !keys[keyCode] && previousKeys[keyCode]; }
        inline static bool GetMouseButton(i32 mouseCode) { return mouse[mouseCode]; }
        inline static bool GetMouseDown(i32 mouseCode) { return mouse[mouseCode] && !previousMouse[mouseCode]; }
        inline static bool GetMouseUp(i32 mouseCode) { return !mouse[mouseCode] && previousMouse[mouseCode]; }
        inline static Vec2 GetMousePosition() { return mousePosition; }
        inline static Vec2 GetMouseDelta() { return mouseDelta; } 
        static void Update(GLFWwindow* window);

    private:
        static bool keys[512];
        static bool previousKeys[512];
        static bool mouse[8];
        static bool previousMouse[8];
        static Vec2 mousePosition;
        static Vec2 previousMousePosition;
        static Vec2 mouseDelta;
        static bool firstMouseMove;
    };
}

#endif