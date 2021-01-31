#ifndef WINDOW_H
#define WINDOW_H

#include "../Common/OpenGL.h"


class Window {

public:  
    Window();

    GLFWwindow* _glWindow;
};

void KeyPressed(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);


#endif