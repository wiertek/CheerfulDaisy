#include <iostream>
#include <cstdlib>
#include <functional>

#include "Window.h"
#include "..\Engine\OpenGLRenderer.h"

Window::Window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    _glWindow = glfwCreateWindow(viewportWidth, viewportHeight, "Cheerful Daisy", NULL, NULL);
    OpenGLRenderer::getInstance().setViewportSize(viewportWidth, viewportHeight);
    if (_glWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(_glWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    glViewport(0, 0, viewportWidth, viewportHeight);
    using namespace std::placeholders;
    glfwSetWindowUserPointer(_glWindow, this);
    glfwSetFramebufferSizeCallback(_glWindow, Window::SizeChangedCallback);
}

void Window::SizeChangedCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    OpenGLRenderer::getInstance().setViewportSize(width, height);
}

