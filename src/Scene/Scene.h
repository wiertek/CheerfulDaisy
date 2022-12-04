#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../Common/Definitions.h"
#include "Primitive.h"

class Scene {
    struct InitialSettings {
        glm::vec3 cameraPosition{glm::vec3(0.0f, 0.0f, 0.0f)};
        LightSource lightSource = {
            .ambient = glm::vec3(0.2f, 0.2f, 0.2f),
            .diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
            .specular = glm::vec3(1.0f, 1.0f, 1.0f),
        };
        Material material = {.ambient = glm::vec3(1.0f, 1.0f, 1.0f),
                             .diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
                             .specular = glm::vec3(1.0f, 1.0f, 1.0f),
                             .shininess = 32.0f};
    };

  public:
    std::unique_ptr<Primitive>& add(std::unique_ptr<Primitive> primitive);
    const std::vector<std::unique_ptr<Primitive>>& getPrimitives() const;

    InitialSettings initialSettings;

  private:
    std::vector<std::unique_ptr<Primitive>> primitives_;
};

#endif