#ifndef DAISYENGINE_H
#define DAISYENGINE_H

#include "../Common/OpenGL.h"
#include "OpenGLRenderer.h"

class DaisyEngine {


public:
    void MainLoop();

private:
    void processKeyboardInput(GLFWwindow *window, double deltaTime);
    static void ProcessMouseInput(GLFWwindow* window, double xpos, double ypos);

    OpenGLRenderer* _openGLRenderer{ nullptr };
};

#endif