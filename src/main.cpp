#include <window.hpp>
#include <graphics/engine.hpp>
#include <cstdio>

int main() {
    // Initialization of the window and the graphics engine.
    Window window(124, 78, "Pseudo Minecraft", GraphicsEngine::windowSetup);
    GraphicsEngine engine(window.glfwPointer());
    // Some variables for performance measurement.
    unsigned long long frames = 0;
    double start = glfwGetTime();
    // Main loop.
    while (window.opened()) {
        engine.update();
        window.update();
        frames++;
    }
    // Printing the average time per frame in milliseconds.
    double millis = (glfwGetTime() - start) / frames * 1000;
    printf("Average ms per frame: ");
    if (millis > 33.33) printf("\033[1;31m%fms\033[0m\n", millis); // If less than 30FPS, print red.
    else if (millis > 16.67) printf("\033[1;33m%fms\033[0m\n", millis); // If less than 60FPS, print yellow.
    else printf("\033[1;32m%fms\033[0m\n", millis); // If 60FPS or more, print green.
    return 0;
}