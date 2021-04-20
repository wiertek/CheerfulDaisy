#include "Scene.h"

std::unique_ptr<Primitive>& Scene::Add(std::unique_ptr<Primitive> primitive) {
    _primitives.push_back(std::move(primitive));
    return _primitives.back();
}

const std::vector<std::unique_ptr<Primitive>>& Scene::GetPrimitives() const {
    return _primitives;
}
