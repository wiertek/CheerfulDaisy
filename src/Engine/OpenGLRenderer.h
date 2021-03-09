#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "../Scene/Scene.h"
#include "../Common/OpenGL.h"
#include <array>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Camera.h"

struct Object {
    unsigned int VBO; 
    unsigned int VAO; 
    size_t verticesNum;
    glm::mat4 model{ glm::mat4(1.0f) };
};

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
    void DrawFrame(GLFWwindow* window);
    void processKeyboardInput(int key, double deltaTime);
    void processMouseInput(int key, double xOffset, double yOffset);
    void setViewportSize(int width, int height);

private:
    OpenGLRenderer() {}
    std::vector<float> UnpackVertices(const std::vector<Triangle>& triangles);

    std::vector<Object> _objectsToRender;
    Shader _currentShader;
    Camera _camera;
    int _width;
    int _height;
};

#endif