#ifndef SCENE_H
#define SCENE_H

#include "../Common/Definitions.h"
#include "Primitive.h"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class Scene {
  public:
    
    std::unique_ptr<Primitive> &Add(std::unique_ptr<Primitive> primitive);
    const std::vector<std::unique_ptr<Primitive>> &GetPrimitives() const;

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

    InitialSettings initialSettings;

  private:
    std::vector<std::unique_ptr<Primitive>> _primitives;
};

#endif