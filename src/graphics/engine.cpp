#include <graphics/engine.hpp>
#include <glad/glad.h>
#include <stdexcept>
#include <fstream>

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
    glClearColor(0, 0, 0, 1);
}
GraphicsEngine::~GraphicsEngine() {
    glDeleteProgram(program);
}
void GraphicsEngine::update() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (Mesh* mesh: meshes) mesh->draw();
}
void GraphicsEngine::windowSetup() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GraphicsEngine::applyShaders(const char* vertexPath, const char* fragmentPath) {
    int success;
    char errMsg[1024];
    // Vertex shader
    std::ifstream vertexFile(vertexPath);
    if (!vertexFile) throw std::runtime_error("Failed to open vertex shader file.");
    vertexFile.seekg(0, std::ios::end);
    unsigned int vertexSize = vertexFile.tellg();
    vertexFile.seekg(0);
    char* vertexSource = new char[vertexSize + 1];
    vertexFile.read(vertexSource, vertexSize);
    vertexFile.close();
    vertexSource[vertexSize] = '\0';
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    delete[] vertexSource;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 1024, nullptr, errMsg);
        throw std::runtime_error(errMsg);
    }
    // Fragment shader
    std::ifstream fragmentFile(fragmentPath);
    if (!fragmentFile) throw std::runtime_error("Failed to open fragment shader file.");
    fragmentFile.seekg(0, std::ios::end);
    unsigned int fragmentSize = fragmentFile.tellg();
    fragmentFile.seekg(0);
    char* fragmentSource = new char[fragmentSize + 1];
    fragmentFile.read(fragmentSource, fragmentSize);
    fragmentFile.close();
    fragmentSource[fragmentSize] = '\0';
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    delete[] fragmentSource;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 1024, nullptr, errMsg);
        throw std::runtime_error(errMsg);
    }
    // Shader program
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, nullptr, errMsg);
        throw std::runtime_error(errMsg);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(program);
}
void GraphicsEngine::addMesh(Mesh* mesh) {
    meshes.push_back(mesh);
}