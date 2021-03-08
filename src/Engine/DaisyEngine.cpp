#include "DaisyEngine.h"
#include "../Interface/Window.h"
#include "../Common/OpenGL.h"
#include "../Interface/FpsLimiter.h"
#include "../Scene/Scene.h"
#include "../Scene/Box.h"
#include "Camera.h"
#include "OpenGLRenderer.h"
#include <glm/glm.hpp>
#include <memory>

constexpr auto TARGET_FPS = 60_fps;

Scene buildSimpleScene();
void ProcessInput(GLFWwindow *window);

void DaisyEngine::MainLoop() {

    Window window;
    FpsLimiter fpsLimiter(TARGET_FPS);
    _openGLRenderer = &OpenGLRenderer::getInstance();
    auto simpleScene = buildSimpleScene();
    _openGLRenderer->LoadScene(simpleScene);
    
    double lastFrame = 0;
    double deltaTime = 0;
    while (!glfwWindowShouldClose(window._glWindow))
    {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        _openGLRenderer->DrawFrame(window._glWindow);
        
        glfwPollEvents();
        ProcessKeyboardInput(window._glWindow, deltaTime);
        fpsLimiter.FrameEnd();
    }

    glfwTerminate();
}

//TODO mock
Scene buildSimpleScene() {
    Scene scene;
    scene.Add(std::make_unique<Box>(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f)));
    scene.Add(std::make_unique<Box>(glm::vec3(-2.0f, 0.0f, -2.0f), glm::vec3(-3.0f, 2.0f, -6.0f)));
    scene.cameraInitialPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    return scene;
}

void DaisyEngine::ProcessKeyboardInput(GLFWwindow *window, double deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        _openGLRenderer->processKeyboardInput(GLFW_KEY_W, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        _openGLRenderer->processKeyboardInput(GLFW_KEY_S, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        _openGLRenderer->processKeyboardInput(GLFW_KEY_A, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        _openGLRenderer->processKeyboardInput(GLFW_KEY_D, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        _openGLRenderer->processKeyboardInput(GLFW_KEY_Q, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        _openGLRenderer->processKeyboardInput(GLFW_KEY_E, deltaTime);
    }
        
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);   
    }
}

void DaisyEngine::processMouseInput(GLFWwindow* window, double xpos, double ypos) {

}