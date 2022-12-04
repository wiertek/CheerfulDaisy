#ifndef OVERLAY_H
#define OVERLAY_H

#include "../Common/OpenGL.h"
#include "../Engine/OpenGLRendererSettings.h"
#include "../Scene/Scene.h"
#include <glm/gtc/matrix_transform.hpp>

class Overlay {
  public:
    Overlay(GLFWwindow* window);
    ~Overlay();
    void loadSceneSettings(const Scene& scene);
    void draw();
    Projection getProjection();
    LigthModel getLightModel();
    OpenGLRendererSettings getSettings();

  private:
    int projectionIndex_{0};
    int lightModelIndex_{0};
    float materialAmbient_[3];
    float materialDiffuse_[3];
    float materialSpecular_[3];
    float lightAmbient_[3];
    float lightDiffuse_[3];
    float lightSpecular_[3];

    OpenGLRendererSettings settings_;
};

#endif