#include "OpenGLRenderer.h"
#include "../Common/Definitions.h"
#include "../Common/OpenGL.h"
#include "../Scene/Box.h"
#include "Shaders/Shader.h"
#include <glm/gtc/matrix_transform.hpp>

void OpenGLRenderer::LoadScene(const Scene& scene) {
    const auto& primitives = scene.GetPrimitives();
    for(auto&& primitive : primitives) {
        auto&& triangles = primitive->GetTriangles();
        std::vector<float>&& verticesAndNormals = UnpackVerticesAndNormals(triangles);

        auto renderObject = Object{};

        glGenBuffers(1, &renderObject.VBO);
        glGenVertexArrays(1, &renderObject.VAO);
        glBindVertexArray(renderObject.VAO); 
        glBindBuffer(GL_ARRAY_BUFFER, renderObject.VBO);
        auto size = verticesAndNormals.size() * sizeof(float);
        glBufferData(GL_ARRAY_BUFFER, verticesAndNormals.size() * sizeof(float), verticesAndNormals.data(), GL_STATIC_DRAW); 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);  

        renderObject.color = primitive->color;
        renderObject.verticesNum = verticesAndNormals.size() / (3*2);
        _objectsToRender.push_back(std::move(renderObject));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }    
    _lightSource = std::move(scene.lightSource);
    GenerateLightObject(_lightSource);
    _simpleShader = SimpleShader("Shaders/SimpleVertexShader.glsl", "Shaders/SimpleFragmentShader.glsl");
    _phongShader = PhongShader("Shaders/PhongVertexShader.glsl", "Shaders/PhongFragmentShader.glsl");
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST); 
    _currentShader = &_phongShader;
   //_simpleShader.Use();

    _camera.setPosition(scene.cameraInitialPosition);
}

void OpenGLRenderer::DrawFrame(GLFWwindow* window, const OpenGLRendererSettings& settings) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(settings.projection == Projection::PERSPECTIVE) {
        _drawingInfo.projection = glm::perspective(settings.fieldOfView, static_cast<float>(_width)/_height, settings.frustumMin, settings.frustumMax);
    } else {
        auto aspectRatio = _width / _height;
        _drawingInfo.projection = glm::ortho(-settings.orthoFieldOfViewFactor * aspectRatio,
            settings.orthoFieldOfViewFactor * aspectRatio,
            -settings.orthoFieldOfViewFactor,
            settings.orthoFieldOfViewFactor, settings.frustumMin, settings.frustumMax);
    }
    
    _currentShader->Use();
    for(auto&& object : _objectsToRender) {
        glBindVertexArray(object.VAO); // use VAO which tells what to draw
        _currentShader->SetParamsForObject(_drawingInfo, object, _camera, _lightSource);
        glDrawArrays(GL_TRIANGLES, 0, object.verticesNum); 
    }

    _lightShader.Use();
    _lightShader.SetMat4f("projection", _drawingInfo.projection);
    _lightShader.SetMat4f("model", lightObject.model);
    _lightShader.SetMat4f("view", _camera.getViewMatrix());
    glBindVertexArray(this->lightObject.VAO);
    glDrawArrays(GL_TRIANGLES, 0, lightObject.verticesNum); 
}

void OpenGLRenderer::processKeyboardInput(int key, double deltaTime) {
    switch(key) {
        case GLFW_KEY_W: 
        case GLFW_KEY_S:
        case GLFW_KEY_A: 
        case GLFW_KEY_D:
        case GLFW_KEY_Q:
        case GLFW_KEY_E:
        case GLFW_KEY_R:
        case GLFW_KEY_F:
            _camera.processKeyboard(key, deltaTime);
            break;
    }
}

void OpenGLRenderer::processMouseInput(int key, double xOffset, double yOffset) {
    if(key == GLFW_MOUSE_BUTTON_MIDDLE) {
        _camera.processMouse(key, xOffset, yOffset);
    }
}

void OpenGLRenderer::setViewportSize(int width, int height) {
    _width = width;
    _height = height;
}

std::vector<float> OpenGLRenderer::UnpackVerticesAndNormals(const std::vector<Triangle>& triangles) {
    std::vector<float> verticesAndNormals;
    verticesAndNormals.reserve(3 * triangles.size());
    for(auto&& triangle : triangles) {
        for(auto i = 0; i < 3; i++) {
            verticesAndNormals.push_back(triangle.vertices[i].x);
            verticesAndNormals.push_back(triangle.vertices[i].y);
            verticesAndNormals.push_back(triangle.vertices[i].z);
            verticesAndNormals.push_back(triangle.normal.x);
            verticesAndNormals.push_back(triangle.normal.y);
            verticesAndNormals.push_back(triangle.normal.z);
        }    
    }
    return verticesAndNormals;
}

void OpenGLRenderer::GenerateLightObject(const LightSource& lightSource) {
    constexpr auto lightBoxRadius = 0.5f;
    auto&& lightPosition = lightSource.position;
    auto lightBox = Box(lightPosition - glm::vec3(lightBoxRadius),
        lightPosition + glm::vec3(lightBoxRadius));

    auto lightObject = Object{};
    glGenBuffers(1, &lightObject.VBO);
    glGenVertexArrays(1, &lightObject.VAO);
    glBindVertexArray(lightObject.VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, lightObject.VBO);
    auto vertices = UnpackVerticesAndNormals(lightBox.GetTriangles());
    auto size = vertices.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);  
    lightObject.verticesNum = vertices.size() / 3;
    this->lightObject = std::move(lightObject);

    _lightShader = SimpleShader("Shaders/LightVertexShader.glsl", "Shaders/LightFragmentShader.glsl");
}