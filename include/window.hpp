#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window {
    public:
        // Creates a window with the specified parameters.
        // `graphicsSetup` is a static function that should be provided by the graphics engine, required for appropriate configuration.
        Window(int width, int height, const char* title, void (*graphicsSetup)());
        ~Window();
        // Swaps buffers, polls events and etc.
        void update();
        // Returns false if the window should close, otherwise true.
        // Meant to be used in the main loop.
        bool opened();
        // Returns a GLFWwindow* pointer to the window.
        GLFWwindow* glfwPointer();
    private:
        GLFWwindow* window;
};