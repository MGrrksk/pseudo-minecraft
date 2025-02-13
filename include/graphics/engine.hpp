#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class GraphicsEngine {
    public:
        GraphicsEngine(GLFWwindow* window);
        ~GraphicsEngine();
        // Draws the next frame.
        void update();
        // This function has to be given to the window constructor for proper initialization.
        static void windowSetup();
};