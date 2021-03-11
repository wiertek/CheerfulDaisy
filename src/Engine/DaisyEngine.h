#ifndef DAISYENGINE_H
#define DAISYENGINE_H

#include <memory>

#include "../Common/OpenGL.h"
#include "OpenGLRenderer.h"
#include "../Interface/Overlay.h"

class DaisyEngine {


public:
    void MainLoop();

private:
    void processKeyboardInput(GLFWwindow *window, double deltaTime);
    static void ProcessMouseInput(GLFWwindow* window, double xpos, double ypos);

    OpenGLRenderer* _openGLRenderer{ nullptr };
    std::unique_ptr<Overlay> _overlay;
};

#endif