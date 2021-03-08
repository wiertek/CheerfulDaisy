#ifndef DAISYENGINE_H
#define DAISYENGINE_H

#include "../Common/OpenGL.h"
#include "OpenGLRenderer.h"

class DaisyEngine {


public:
    void MainLoop();

private:
    void ProcessKeyboardInput(GLFWwindow *window, double deltaTime);
    void processMouseInput(GLFWwindow* window, double xpos, double ypos);

    OpenGLRenderer* _openGLRenderer{ nullptr };
};

#endif