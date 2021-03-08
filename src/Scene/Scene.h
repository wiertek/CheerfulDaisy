#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Primitive.h"


class Scene {
public:
    glm::vec3 cameraInitialPosition{ glm::vec3(0.0f, 0.0f, 0.0f) };

    std::unique_ptr<Primitive>& Scene::Add(std::unique_ptr<Primitive> primitive);
    const std::vector<std::unique_ptr<Primitive>>& GetPrimitives() const;

private:
    std::vector<std::unique_ptr<Primitive>> _primitives;
};

#endif