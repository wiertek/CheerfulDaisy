#include "Plain.h"

#include <cmath>

Plain::Plain(glm::vec3 from, float yLevel, glm::vec3 to) {
    auto pos = glm::vec3((from.x + to.x) / 2.0, yLevel, (from.z + to.z) / 2.0);
    auto xRadius = std::abs(pos.x - from.x);
    auto zRadius = std::abs(pos.z - from.z);
    auto leftFrontCorner = glm::vec3(-xRadius, 0.0f, -zRadius);
    auto rightTopBackCorner = glm::vec3(xRadius, 0.0f, zRadius);
    vertices_[0] = glm::vec3{leftFrontCorner.x, 0.0f, leftFrontCorner.z};
    vertices_[1] = glm::vec3{leftFrontCorner.x, 0.0f, rightTopBackCorner.z};
    vertices_[2] = glm::vec3{rightTopBackCorner.x, 0.0f, rightTopBackCorner.z};
    vertices_[3] = glm::vec3{rightTopBackCorner.x, 0.0f, leftFrontCorner.z};
    modelMatrix_ = glm::translate(glm::mat4(1.0f), pos);
}

std::vector<Triangle> Plain::getTriangles() {
    std::vector<Triangle> triangles;
    triangles.reserve(2);
    triangles.push_back({{vertices_[0], vertices_[1], vertices_[2]}, glm::vec3{0, 0, 1}});
    triangles.push_back({{vertices_[2], vertices_[3], vertices_[0]}, glm::vec3{0, 0, 1}});
    return triangles;
}

glm::mat4 Plain::getModelMatrix() { return modelMatrix_; }

std::vector<float> Plain::getVerticesWithCoords() {
    std::vector<float> verticesAndCoords;
    verticesAndCoords.reserve(4 * (3 + 2));
    verticesAndCoords.push_back(vertices_[0].x);
    verticesAndCoords.push_back(vertices_[0].y);
    verticesAndCoords.push_back(vertices_[0].z);
    verticesAndCoords.push_back(-1.0f);
    verticesAndCoords.push_back(-1.0f);

    verticesAndCoords.push_back(vertices_[1].x);
    verticesAndCoords.push_back(vertices_[1].y);
    verticesAndCoords.push_back(vertices_[1].z);
    verticesAndCoords.push_back(-1.0f);
    verticesAndCoords.push_back(1.0f);

    verticesAndCoords.push_back(vertices_[2].x);
    verticesAndCoords.push_back(vertices_[2].y);
    verticesAndCoords.push_back(vertices_[2].z);
    verticesAndCoords.push_back(1.0f);
    verticesAndCoords.push_back(1.0f);

    verticesAndCoords.push_back(vertices_[3].x);
    verticesAndCoords.push_back(vertices_[3].y);
    verticesAndCoords.push_back(vertices_[3].z);
    verticesAndCoords.push_back(1.0f);
    verticesAndCoords.push_back(-1.0f);

    return verticesAndCoords;
}

std::vector<int> Plain::getIndices() { return {0, 1, 3, 1, 2, 3}; }