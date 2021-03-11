#ifndef OVERLAY_H
#define OVERLAY_H

#include "../Common/OpenGL.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Engine/OpenGLRendererSettings.h"

class Overlay  {
public:
    Overlay(GLFWwindow* window);
    ~Overlay();
    void draw();
    OpenGLRendererSettings getSettings();
    Projection getProjection();

private:
    int _projectionIndex{ 0 };
    float _fieldOfView{glm::radians(45.0f)};
    float _orthoFieldOfViewFactor{3.0f};
    float _frustumMin{0.1f};
    float _frustumMax{100.0f};
};

#endif