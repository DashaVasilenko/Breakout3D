#ifndef FRAMEWORK_WINDOW_H
#define FRAMEWORK_WINDOW_H

#include <GL/glew.h>
#define GLEW_STATIC

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <string>

#include "../core/types.h"

namespace Bubble {
    class Window {
    public:
        inline static Window* GetInstance() { if (!instance) instance = new Window(); return instance; }

        void SetWidth(i32 width) { this->width = width; }
        void SetHeight(i32 height) { this->height = height; }
        void SetName(const std::string& name) { this->name = name; }

        GLFWwindow* GetPointer() { return this->window; }
        i32 GetWidth() { return width; }
        i32 GetHeight() { return height; }

        i32 Init();

        static void ErrorCallback(i32 error, const char* description);
        static void OnKeyPressed(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mode);
        static void OnMouseMove(GLFWwindow* window, double xpos, double ypos);
        static void MouseButtonCallback(GLFWwindow* window, i32 button, i32 action, i32 mods);
        static void WindowSizeCallback(GLFWwindow* window, int width, int height);

        ~Window();

    private:
        GLFWwindow* window = nullptr; 
        i32 width = 640;
        i32 height = 480;
        std::string name = "Window";

        static Window* instance;
        Window() {}
    };  
}

#endif /* End of FRAMEWORK_WINDOW_H */ 