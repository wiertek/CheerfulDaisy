#include <iostream>
#include <cstdlib>
#include <functional>

#include "Window.h"

Window::Window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    this->_glWindow = glfwCreateWindow(800, 600, "Cheerful Daisy", NULL, NULL);
    if (this->_glWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(this->_glWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    glViewport(0, 0, 800, 600);
    using namespace std::placeholders;
    glfwSetWindowUserPointer(this->_glWindow, this);
    glfwSetKeyCallback(this->_glWindow, KeyPressed);
}

void KeyPressed(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
    auto& window = *static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

     if (key == GLFW_KEY_ESCAPE) {
         glfwSetWindowShouldClose(glfwWindow, true);  
     }
}
