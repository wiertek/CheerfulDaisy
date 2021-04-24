#ifndef OVERLAY_H
#define OVERLAY_H

#include "../Common/OpenGL.h"
#include "../Scene/Scene.h"
#include "../Engine/OpenGLRendererSettings.h"
#include <glm/gtc/matrix_transform.hpp>


class Overlay {
public:
  Overlay(GLFWwindow *window);
  void LoadSceneSettings(const Scene& scene);
  ~Overlay();
  void Draw();
  Projection GetProjection();
  LigthModel GetLightModel();
  OpenGLRendererSettings GetSettings();

 

private:
  int _projectionIndex{0};
  int _lightModelIndex{0};
  float _materialAmbient[3];
  float _materialDiffuse[3];
  float _materialSpecular[3];
  float _shininess;
  float _lightAmbient[3];
  float _lightDiffuse[3];
  float _lightSpecular[3];

   OpenGLRendererSettings _settings;
};

#endif