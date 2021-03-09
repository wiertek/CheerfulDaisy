#ifndef WINDOW_H
#define WINDOW_H

#include "../Common/OpenGL.h"

constexpr auto viewportHeight = 600;
constexpr auto viewportWidth = 800;

class Window {

public:  
    Window();

    GLFWwindow* _glWindow;
    static void SizeChangedCallback(GLFWwindow* window, int width, int height);
};



#endif