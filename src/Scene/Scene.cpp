#include "Scene.h"

std::unique_ptr<Primitive>& Scene::add(std::unique_ptr<Primitive> primitive) {
    primitives_.push_back(std::move(primitive));
    return primitives_.back();
}

const std::vector<std::unique_ptr<Primitive>>& Scene::getPrimitives() const { return primitives_; }
