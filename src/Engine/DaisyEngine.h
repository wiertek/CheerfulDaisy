#ifndef DAISYENGINE_H
#define DAISYENGINE_H

#include <memory>

#include "../Common/OpenGL.h"
#include "../Interface/Overlay.h"
#include "OpenGLRenderer.h"

class DaisyEngine {

  public:
    void mainLoop();

  private:
    void processKeyboardInput(GLFWwindow* window, double deltaTime);
    static void ProcessMouseInput(GLFWwindow* window, double xpos, double ypos);

    OpenGLRenderer* openGLRenderer_{nullptr};
    std::unique_ptr<Overlay> overlay_;
};

#endif