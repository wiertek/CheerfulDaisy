#include "OpenGLRenderer.h"
#include "../Common/Definitions.h"
#include "../Common/OpenGL.h"
#include "../Scene/Plain.h"
#include "Shaders/Shader.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

void OpenGLRenderer::loadScene(const Scene& scene) {
    const auto& primitives = scene.getPrimitives();

    for (auto&& primitive : primitives) {
        auto&& triangles = primitive->getTriangles();
        std::vector<float>&& verticesAndNormals = unpackVerticesAndNormals(triangles);

        auto renderObject = Object{};

        glGenBuffers(1, &renderObject.VBO);
        glGenVertexArrays(1, &renderObject.VAO);
        glBindVertexArray(renderObject.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, renderObject.VBO);
        glBufferData(GL_ARRAY_BUFFER, verticesAndNormals.size() * sizeof(float), verticesAndNormals.data(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        renderObject.verticesNum = verticesAndNormals.size() / (3 * 2);
        renderObject.model = primitive->getModelMatrix();
        objectsToRender_.push_back(std::move(renderObject));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    lightSource_ = scene.initialSettings.lightSource;
    generateLightObject(lightSource_);
    drawingInfo_.lightSource = &lightSource_;
    simpleShader_ = SimpleShader("Shaders/SimpleVertexShader.glsl", "Shaders/SimpleFragmentShader.glsl");
    phongShader_ = PhongShader("Shaders/PhongVertexShader.glsl", "Shaders/PhongFragmentShader.glsl");
    gouraudShader_ = GouraudShader("Shaders/GouraudVertexShader.glsl", "Shaders/GouraudFragmentShader.glsl");
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    camera_.position_ = scene.initialSettings.cameraPosition;
    drawingInfo_.camera = &camera_;
}

void OpenGLRenderer::drawFrame(const OpenGLRendererSettings& settings) {
    if (width_ == 0 || height_ == 0) { // may happen during minimizing window
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (settings.projection == Projection::PERSPECTIVE) {
        drawingInfo_.projection = glm::perspective(settings.fieldOfView, static_cast<float>(width_) / height_,
                                                   settings.frustumMin, settings.frustumMax);
    } else {
        auto aspectRatio = width_ / height_;
        drawingInfo_.projection =
            glm::ortho(-settings.orthoFieldOfViewFactor * aspectRatio, settings.orthoFieldOfViewFactor * aspectRatio,
                       -settings.orthoFieldOfViewFactor, settings.orthoFieldOfViewFactor, settings.frustumMin,
                       settings.frustumMax);
    }
    switch (settings.lightModel) {
        case LigthModel::NONE: currentShader_ = &simpleShader_; break;
        case LigthModel::PHONG: currentShader_ = &phongShader_; break;
        case LigthModel::GOURAUD: currentShader_ = &gouraudShader_; break;
    }

    currentShader_->use();
    for (auto&& object : objectsToRender_) {
        glBindVertexArray(object.VAO);
        currentShader_->setParamsForObject(drawingInfo_, object, settings);
        glDrawArrays(GL_TRIANGLES, 0, object.verticesNum);
    }

    lightShader_.use();
    lightShader_.setMat4f("model", getLightSourceModelMatrix());
    lightShader_.setMat4f("view", camera_.getViewMatrix());
    lightShader_.setMat4f("projection", drawingInfo_.projection);
    lightShader_.setVec3("color", settings.lightSource.specular);
    glBindVertexArray(this->lightObject_.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLRenderer::processKeyboardInput(int key, double deltaTime) {
    switch (key) {
        case GLFW_KEY_W:
        case GLFW_KEY_S:
        case GLFW_KEY_A:
        case GLFW_KEY_D:
        case GLFW_KEY_Q:
        case GLFW_KEY_E:
        case GLFW_KEY_R:
        case GLFW_KEY_F: camera_.processKeyboard(key, deltaTime); break;
    }
}

void OpenGLRenderer::processMouseInput(int key, double xOffset, double yOffset) {
    if (key == GLFW_MOUSE_BUTTON_MIDDLE) {
        camera_.processMouse(key, xOffset, yOffset);
    }
}

void OpenGLRenderer::setViewportSize(int width, int height) {
    width_ = width;
    height_ = height;
}

std::vector<float> OpenGLRenderer::unpackVerticesAndNormals(const std::vector<Triangle>& triangles) {
    std::vector<float> verticesAndNormals;
    verticesAndNormals.reserve(3 * triangles.size());
    for (auto&& triangle : triangles) {
        for (auto i = 0; i < 3; i++) {
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

void OpenGLRenderer::generateLightObject(const LightSource& lightSource) {
    constexpr auto lightBoxRadius = 0.3f;
    auto&& lightPosition = lightSource.position;
    auto lightPlain =
        Plain(lightPosition - glm::vec3(lightBoxRadius), lightPosition.y, lightPosition + glm::vec3(lightBoxRadius));
    auto lightObject = Object{};
    glGenBuffers(1, &lightObject.EBO);
    glGenBuffers(1, &lightObject.VBO);
    glGenVertexArrays(1, &lightObject.VAO);
    glBindVertexArray(lightObject.VAO);

    auto vertices = lightPlain.getVerticesWithCoords();

    auto indices = lightPlain.getIndices();

    glBindBuffer(GL_ARRAY_BUFFER, lightObject.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightObject.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    lightObject.model = lightPlain.getModelMatrix();
    this->lightObject_ = std::move(lightObject);
    lightShader_ = SimpleShader("Shaders/LightVertexShader.glsl", "Shaders/LightFragmentShader.glsl");
}

glm::mat4 OpenGLRenderer::getLightSourceModelMatrix() {
    glm::vec3 direction = glm::normalize(camera_.position_ - lightSource_.position);
    glm::mat4 model = glm::mat4(1.0f);
    model = lightObject_.model;

    auto directionInXPlane = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));
    float angle = std::acos(directionInXPlane.x);
    if (directionInXPlane.z > 0) {
        angle *= -1;
    }

    glm::vec3 right = glm::normalize(glm::cross(directionInXPlane, glm::vec3(0.0f, 1.0f, 0.0f)));
    float angleY = std::acos(direction.x * directionInXPlane.x + direction.z * directionInXPlane.z);
    if (direction.y > 0) {
        angleY *= -1;
    }

    model = glm::rotate(model, 1.57f - angleY, right);
    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    return model;
}