#include <window.hpp>
#include <stdexcept>

Window::Window(int width, int height, const char* title, void (*graphicsSetup)()) {
    if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW.");
    graphicsSetup();
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }
}
Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
bool Window::opened() {
    return !glfwWindowShouldClose(window);
}
GLFWwindow* Window::glfwPointer() {
    return window;
}