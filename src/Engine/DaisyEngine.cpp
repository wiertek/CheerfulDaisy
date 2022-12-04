#include "DaisyEngine.h"
#include "../Common/OpenGL.h"
#include "../Interface/FpsLimiter.h"
#include "../Interface/Window.h"
#include "../Scene/Box.h"
#include "../Scene/Scene.h"
#include "Camera.h"
#include "OpenGLRenderer.h"
#include <glm/glm.hpp>
#include <memory>

constexpr auto TARGET_FPS = 60_fps;

Scene buildSimpleScene();
void ProcessInput(GLFWwindow* window);

void DaisyEngine::mainLoop() {

    Window window;
    FpsLimiter fpsLimiter(TARGET_FPS);
    openGLRenderer_ = &OpenGLRenderer::getInstance();
    auto simpleScene = buildSimpleScene();
    openGLRenderer_->loadScene(simpleScene);
    overlay_ = std::make_unique<Overlay>(window.glWindow_);
    overlay_->loadSceneSettings(simpleScene);
    glfwSetCursorPosCallback(window.glWindow_, DaisyEngine::ProcessMouseInput);

    double lastFrame = 0;
    double deltaTime = 0;
    auto measureDeltaTime = [&lastFrame, &deltaTime]() {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    };

    while (!glfwWindowShouldClose(window.glWindow_)) {
        measureDeltaTime();

        openGLRenderer_->drawFrame(overlay_->getSettings());
        overlay_->draw();

        glfwSwapBuffers(window.glWindow_);
        glfwPollEvents();
        processKeyboardInput(window.glWindow_, deltaTime);
        fpsLimiter.frameEnd();
    }

    glfwTerminate();
}

Scene buildSimpleScene() {
    Scene scene;
    scene.add(std::make_unique<Box>(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f)));
    scene.add(std::make_unique<Box>(glm::vec3(-2.0f, 0.0f, -2.0f), glm::vec3(-3.0f, 2.0f, -6.0f)));
    scene.initialSettings.lightSource.position = glm::vec3(2.0f, 2.0f, -2.0f);
    scene.initialSettings.cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    scene.initialSettings.material.ambient = glm::vec3(1.0f, 0.4f, 0.0f);
    scene.initialSettings.material.shininess = 32.0f;
    return scene;
}

void DaisyEngine::processKeyboardInput(GLFWwindow* window, double deltaTime) {
    assert(openGLRenderer_ != nullptr);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        openGLRenderer_->processKeyboardInput(GLFW_KEY_W, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        openGLRenderer_->processKeyboardInput(GLFW_KEY_S, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        openGLRenderer_->processKeyboardInput(GLFW_KEY_A, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        openGLRenderer_->processKeyboardInput(GLFW_KEY_D, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        openGLRenderer_->processKeyboardInput(GLFW_KEY_Q, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        openGLRenderer_->processKeyboardInput(GLFW_KEY_E, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        openGLRenderer_->processKeyboardInput(GLFW_KEY_R, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        openGLRenderer_->processKeyboardInput(GLFW_KEY_F, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void DaisyEngine::ProcessMouseInput(GLFWwindow* window, double xpos, double ypos) {
    static auto&& openGLRenderer = OpenGLRenderer::getInstance();
    static bool firstMouse = true;
    static double lastX{0}, lastY{0};
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    auto xOffset = xpos - lastX;
    auto yOffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
        openGLRenderer.processMouseInput(GLFW_MOUSE_BUTTON_MIDDLE, xOffset, yOffset);
    }
}