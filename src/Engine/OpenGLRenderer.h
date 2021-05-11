#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "../Scene/Scene.h"
#include "../Common/OpenGL.h"
#include "OpenGLRendererSettings.h"
#include <array>
#include <glm/glm.hpp>
#include "Shaders/Shader.h"
#include "Shaders/SimpleShader.h"
#include "Shaders/PhongShader.h"
#include "Shaders/GouraudShader.h"
#include "Camera.h"

class OpenGLRenderer {
public:
    static OpenGLRenderer& getInstance()
    {
        static OpenGLRenderer instance; 
        return instance;
    }
    OpenGLRenderer(const OpenGLRenderer&) = delete;
    void operator=(const OpenGLRenderer&) = delete;
    
    void LoadScene(const Scene& scene);
    void DrawFrame(GLFWwindow* window, const OpenGLRendererSettings& settings);
    void processKeyboardInput(int key, double deltaTime);
    void processMouseInput(int key, double xOffset, double yOffset);
    void setViewportSize(int width, int height);

private:
    OpenGLRenderer() {}
    std::vector<float> UnpackVerticesAndNormals(const std::vector<Triangle>& triangles);
    void GenerateLightObject(const LightSource& ligthSource);
    glm::mat4 GetLightSourceModelMatrix();

    FrameDrawingInfo _drawingInfo;

    std::vector<Object> _objectsToRender;
    Object lightObject;
    Camera _camera;
    int _width;
    int _height;
    LightSource _lightSource;

    //shaders
    Shader* _currentShader;
    SimpleShader _simpleShader;
    SimpleShader _lightShader;
    PhongShader _phongShader;
    GouraudShader _gouraudShader;

};

#endif