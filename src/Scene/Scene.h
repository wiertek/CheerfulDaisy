#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Primitive.h"
#include "../Common/Definitions.h"

class Scene {
public:
    glm::vec3 cameraInitialPosition{ glm::vec3(0.0f, 0.0f, 0.0f) };
    
    std::unique_ptr<Primitive>& Add(std::unique_ptr<Primitive> primitive);
    const std::vector<std::unique_ptr<Primitive>>& GetPrimitives() const;

    LightSource lightSource = {
        .ambient = glm::vec3(0.2f, 0.2f, 0.2f),
        .diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
        .specular = glm::vec3(1.0f, 1.0f, 1.0f),
    };
    Material material = {
        .ambient = glm::vec3(1.0f, 1.0f, 1.0f),
        .diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
        .specular = glm::vec3(1.0f, 1.0f, 1.0f),
        .shininess = 32.0f
    };

private:
    std::vector<std::unique_ptr<Primitive>> _primitives;

};

#endif