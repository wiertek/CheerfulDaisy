#include "DaisyEngine.h"
#include "../Interface/Window.h"
#include "../Common/OpenGL.h"
#include "../Interface/FpsLimiter.h"

constexpr auto TARGET_FPS = 60_fps;

void DaisyEngine::MainLoop() {

    Window window;
    FpsLimiter fpsLimiter(TARGET_FPS);
    while (!glfwWindowShouldClose(window._glWindow))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window._glWindow);
        glfwPollEvents();

        fpsLimiter.FrameEnd();
    }

    glfwTerminate();
}