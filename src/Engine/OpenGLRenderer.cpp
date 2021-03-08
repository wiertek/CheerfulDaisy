#include "OpenGLRenderer.h"
#include "../Common/Definitions.h"
#include "../Common/OpenGL.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

void OpenGLRenderer::LoadScene(const Scene& scene) {
    const auto& primitives = scene.GetPrimitives();
    for(auto&& primitve : primitives) {
        auto&& triangles = primitve->GetTriangles();
        std::vector<float>&& vertices = UnpackVertices(triangles);

        auto renderObject = Object{};

        glGenBuffers(1, &renderObject.VBO);
        glGenVertexArrays(1, &renderObject.VAO);
        glBindVertexArray(renderObject.VAO); 
        glBindBuffer(GL_ARRAY_BUFFER, renderObject.VBO);
        auto aa = vertices.size();
        auto aaa = sizeof(float);
        auto size = vertices.size() * sizeof(float);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW); 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  

        renderObject.verticesNum = vertices.size() /3 ;
        _objectsToRender.push_back(std::move(renderObject));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }    

    _currentShader = Shader("Shaders/SimpleVertexShader.glsl", "Shaders/SimpleFragmentShader.glsl");
    
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST); 
    _currentShader.Use();

    _camera.Position = scene.cameraInitialPosition;

    glm::mat4 projection;
    float fov = 45.0f;
    projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
    _currentShader.SetMat4f("projection", projection);

}

void OpenGLRenderer::DrawFrame(GLFWwindow* window) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto&& object : _objectsToRender) {
        glBindVertexArray(object.VAO); // use VAO which tells what to draw
        _currentShader.SetMat4f("model", object.model);
        _currentShader.SetMat4f("view", _camera.getViewMatrix());
        glDrawArrays(GL_TRIANGLES, 0, object.verticesNum); 
    }

    glfwSwapBuffers(window);
}

void OpenGLRenderer::processKeyboardInput(int key, double deltaTime) {
    switch(key) {
        case GLFW_KEY_W: 
        case GLFW_KEY_S:
        case GLFW_KEY_A: 
        case GLFW_KEY_D:
        case GLFW_KEY_Q:
        case GLFW_KEY_E:
            _camera.processKeyboard(key, deltaTime);
            break;
    }
}

std::vector<float> OpenGLRenderer::UnpackVertices(const std::vector<Triangle>& triangles) {
    std::vector<float> vertices;
    vertices.reserve(3 * triangles.size());
    for(auto&& triangle : triangles) {
        for(auto i = 0; i < 3; i++) {
            vertices.push_back(triangle[i].x);
            vertices.push_back(triangle[i].y);
            vertices.push_back(triangle[i].z);
        }    
    }
    return vertices;
}
