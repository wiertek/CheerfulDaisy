#ifndef WINDOW_H
#define WINDOW_H

#include "../Common/OpenGL.h"

constexpr auto viewportHeight = 900;
constexpr auto viewportWidth = 1600;

class Window {

  public:
    Window();

    GLFWwindow* glWindow_;
    static void sizeChangedCallback(GLFWwindow* /*window*/, int width, int height);
};

#endif