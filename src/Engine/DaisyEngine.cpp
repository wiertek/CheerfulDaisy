#include "DaisyEngine.h"
#include "../Interface/Window.h"
#include "../Common/OpenGL.h"

void DaisyEngine::MainLoop() {

    Window window;

    while (!glfwWindowShouldClose(window._glWindow))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window._glWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}