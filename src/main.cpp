#include <window.hpp>
#include <graphics/engine.hpp>
#include <cstdio>

void _main() {
    // Initialization of the window and the graphics engine.
    Window window(1024, 768, "Pseudo Minecraft", GraphicsEngine::windowSetup);
    GraphicsEngine engine(window.glfwPointer());
    engine.applyShaders("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
    // Adding meshes.
    float vertices1[] = {
        -0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
        -0.5,  0.5, 0.0, 0.0, 0.0, 1.0,
         0.0, -0.5, 0.0, 0.0, 0.0, 1.0,
    };
    Mesh mesh1(vertices1, sizeof(vertices1), MESH_ATTR_POSITION | MESH_ATTR_COLOR);
    engine.addMesh(&mesh1);
    float vertices2[] = {
        0.5,  0.5, 0.0, 0.0, 1.0, 0.0,
        0.5, -0.5, 0.0, 0.0, 1.0, 0.0,
        0.0,  0.5, 0.0, 0.0, 1.0, 0.0,
    };
    Mesh mesh2(vertices2, sizeof(vertices2), MESH_ATTR_POSITION | MESH_ATTR_COLOR);
    engine.addMesh(&mesh2);
    // Some variables for speed tracking.
    double lastFrame = glfwGetTime();
    double delta;
    unsigned long long frames = 0;
    double millis = 0;
    // Main loop.
    while (window.opened()) {
        // Timing
        delta = glfwGetTime() - lastFrame;
        lastFrame += delta;
        millis += delta;
        frames++;
        // Updating
        engine.update();
        window.update();
    }
    // Printing the average time per frame & FPS.
    double mspf = millis / frames * 1000;
    int fps = 1000 / mspf;
    const char* color;
    if (fps < 30) color = "\033[1;31m"; // red
    else if (fps < 60) color = "\033[1;33m"; // yellow
    else color = "\033[1;32m"; // green
    printf("Average time per frame: %s%fms\033[0m\n", color, mspf);
    printf("Average FPS: %s%d\033[0m\n", color, fps);
}

int main() {
    try {
        _main();
    } catch (const std::exception& e) {
        fprintf(stderr, "Error: %s\n", e.what());
        return 1;
    }
    return 0;
}