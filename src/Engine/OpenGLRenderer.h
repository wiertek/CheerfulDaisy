#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "../Common/OpenGL.h"
#include "../Scene/Scene.h"
#include "Camera.h"
#include "OpenGLRendererSettings.h"
#include "Shaders/GouraudShader.h"
#include "Shaders/PhongShader.h"
#include "Shaders/Shader.h"
#include "Shaders/SimpleShader.h"
#include <array>
#include <glm/glm.hpp>

class OpenGLRenderer {
  public:
    static OpenGLRenderer& getInstance() {
        static OpenGLRenderer instance;
        return instance;
    }

    OpenGLRenderer(const OpenGLRenderer&) = delete;
    void operator=(const OpenGLRenderer&) = delete;

    void loadScene(const Scene& scene);
    void drawFrame(const OpenGLRendererSettings& settings);
    void processKeyboardInput(int key, double deltaTime);
    void processMouseInput(int key, double xOffset, double yOffset);
    void setViewportSize(int width, int height);

  private:
    OpenGLRenderer() {}
    std::vector<float> unpackVerticesAndNormals(const std::vector<Triangle>& triangles);
    void generateLightObject(const LightSource& ligthSource);
    glm::mat4 getLightSourceModelMatrix();

    FrameDrawingInfo drawingInfo_;

    std::vector<Object> objectsToRender_;
    Object lightObject_;
    Camera camera_;
    int width_;
    int height_;
    LightSource lightSource_;

    // shaders
    Shader* currentShader_;
    SimpleShader simpleShader_;
    SimpleShader lightShader_;
    PhongShader phongShader_;
    GouraudShader gouraudShader_;
};

#endif