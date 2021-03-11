#ifndef WINDOW_H
#define WINDOW_H

#include "../Common/OpenGL.h"

constexpr auto viewportHeight = 900;
constexpr auto viewportWidth = 1600;

class Window {

public:  
    Window();

    GLFWwindow* _glWindow;
    static void SizeChangedCallback(GLFWwindow* window, int width, int height);
};



#endif