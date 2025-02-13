#include <graphics/engine.hpp>
#include <glad/glad.h>
#include <stdexcept>

GraphicsEngine::GraphicsEngine(GLFWwindow* window) {
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Invalid GLFW window.");
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD.");
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
}
GraphicsEngine::~GraphicsEngine() {
    // Nothing to do here (at least for now).
}
void GraphicsEngine::update() {
    glClear(GL_COLOR_BUFFER_BIT);
}
void GraphicsEngine::windowSetup() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}