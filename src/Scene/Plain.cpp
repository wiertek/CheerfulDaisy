#include "Plain.h"

#include <cmath>

Plain::Plain(glm::vec3 from, float yLevel, glm::vec3 to) {
    auto pos = glm::vec3((from.x + to.x) / 2.0, yLevel, (from.z + to.z) / 2.0);
    auto xRadius = std::abs(pos.x - from.x);
    auto zRadius = std::abs(pos.z - from.z);
    auto leftFrontCorner = glm::vec3(-xRadius, 0.0f, -zRadius);
    auto rightTopBackCorner = glm::vec3(xRadius, 0.0f, zRadius);
    _vertices[0] = glm::vec3{leftFrontCorner.x, 0.0f, leftFrontCorner.z};
    _vertices[1] = glm::vec3{leftFrontCorner.x, 0.0f, rightTopBackCorner.z};
    _vertices[2] = glm::vec3{rightTopBackCorner.x, 0.0f, rightTopBackCorner.z};
    _vertices[3] = glm::vec3{rightTopBackCorner.x, 0.0f, leftFrontCorner.z};
    _modelMatrix = glm::translate(glm::mat4(1.0f), pos);
}

std::vector<Triangle> Plain::GetTriangles() {
    std::vector<Triangle> triangles;
    triangles.reserve(2);
    triangles.push_back({_vertices[0], _vertices[1], _vertices[2], glm::vec3{0, 0, 1}});
    triangles.push_back({_vertices[2], _vertices[3], _vertices[0], glm::vec3{0, 0, 1}});
    return triangles;
}

glm::mat4 Plain::GetModelMatrix() { return _modelMatrix; }

std::vector<float> Plain::GetVerticesWithCoords() {
    std::vector<float> verticesAndCoords;
    verticesAndCoords.reserve(4 * (3 + 2));
    verticesAndCoords.push_back(_vertices[0].x);
    verticesAndCoords.push_back(_vertices[0].y);
    verticesAndCoords.push_back(_vertices[0].z);
    verticesAndCoords.push_back(-1.0f);
    verticesAndCoords.push_back(-1.0f);

    verticesAndCoords.push_back(_vertices[1].x);
    verticesAndCoords.push_back(_vertices[1].y);
    verticesAndCoords.push_back(_vertices[1].z);
    verticesAndCoords.push_back(-1.0f);
    verticesAndCoords.push_back(1.0f);

    verticesAndCoords.push_back(_vertices[2].x);
    verticesAndCoords.push_back(_vertices[2].y);
    verticesAndCoords.push_back(_vertices[2].z);
    verticesAndCoords.push_back(1.0f);
    verticesAndCoords.push_back(1.0f);

    verticesAndCoords.push_back(_vertices[3].x);
    verticesAndCoords.push_back(_vertices[3].y);
    verticesAndCoords.push_back(_vertices[3].z);
    verticesAndCoords.push_back(1.0f);
    verticesAndCoords.push_back(-1.0f);

    return verticesAndCoords;
}

std::vector<int> Plain::GetIndices() { return {0, 1, 3, 1, 2, 3}; }