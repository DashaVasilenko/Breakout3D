#include "window.h"
#include "input.h"
#include "../renderer/renderer.h"

namespace Bubble{
    Window* Window::instance = nullptr;

    void Window::ErrorCallback(i32 error, const char* description) {
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }

    void Window::OnKeyPressed(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mode) {
        if (key == Key::Escape && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        if (action == GLFW_PRESS) {
            Input::keys[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            Input::keys[key] = false;
        }
    }

    void Window::OnMouseMove(GLFWwindow* window, double xpos, double ypos) {

    }

    void Window::MouseButtonCallback(GLFWwindow* window, i32 button, i32 action, i32 mods) {
        if (action == GLFW_PRESS) {
            Input::mouse[button] = true;
        }
        else if (action == GLFW_RELEASE) {
            Input::mouse[button] = false;
        }
    }

    void Window::WindowSizeCallback(GLFWwindow* window, int width, int height) {
        Window* myWindow = (Window*)glfwGetWindowUserPointer(window);
        width = std::max(20, width);
        height = std::max(20, height);
        myWindow->SetWidth(width);
        myWindow->SetHeight(height);
        Renderer::GetInstance()->ResizeFramebuffer((f32)myWindow->GetWidth(), (f32)myWindow->GetHeight());
    }

    i32 Window::Init() {
        glfwSetErrorCallback(ErrorCallback);
        if (!glfwInit())
            exit(EXIT_FAILURE);

 	    // Window creation + GL context
 	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
 	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
 	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
 	    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // Resize window

        // Mac OS build fix
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

        window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        if (!window) {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetWindowSizeLimits(window, 640, 480, GLFW_DONT_CARE, GLFW_DONT_CARE); 	

        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetWindowUserPointer(window, this);
        glfwSetCursorPosCallback(window, OnMouseMove);
        glfwSetKeyCallback(window, OnKeyPressed); 
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetWindowSizeCallback(window, WindowSizeCallback);

 	    glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        #ifndef __APPLE__
 	        glewExperimental = true; 
 	        if (glewInit() != GLEW_OK) { glfwTerminate(); return -1; }
        #endif

        return 0;
    }  

    Window::~Window() {
        if (window) {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    }

    
}