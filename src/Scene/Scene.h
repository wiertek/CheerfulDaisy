#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Primitive.h"

struct LightSource {
    glm::vec3 position;
    glm::vec3 color{ glm::vec3(1.0f, 1.0f, 1.0f) };
};

class Scene {
public:
    glm::vec3 cameraInitialPosition{ glm::vec3(0.0f, 0.0f, 0.0f) };
    
    std::unique_ptr<Primitive>& Add(std::unique_ptr<Primitive> primitive);
    const std::vector<std::unique_ptr<Primitive>>& GetPrimitives() const;

    LightSource lightSource;

private:
    std::vector<std::unique_ptr<Primitive>> _primitives;

};

#endif