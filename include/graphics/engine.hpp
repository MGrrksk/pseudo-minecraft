#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <vector>
#include <graphics/mesh.hpp>

class GraphicsEngine {
    unsigned int program;
    std::vector<Mesh*> meshes;
    public:
        GraphicsEngine(GLFWwindow* window);
        ~GraphicsEngine();
        void update();
        // This function has to be given to the window constructor for proper initialization.
        static void windowSetup();
        void applyShaders(const char* vertexPath, const char* fragmentPath);
        void addMesh(Mesh* mesh);
};