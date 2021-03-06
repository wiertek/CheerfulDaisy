#include "Box.h"
#include <algorithm>
#include <cmath>

Box::Box(glm::vec3 from, glm::vec3 to) {
    auto pos = glm::vec3((from.x + to.x) / 2.0, (from.y + to.y) / 2.0, (from.z + to.z) / 2.0);
    auto xRadius = std::abs(pos.x - from.x);
    auto yRadius = std::abs(pos.y - from.y);
    auto zRadius = std::abs(pos.z - from.z);
    auto leftBottomFrontCorner = glm::vec3(-xRadius, -yRadius, zRadius);
    auto rightTopBackCorner = glm::vec3(xRadius, yRadius, -zRadius);
    _vertices[0] = glm::vec3{leftBottomFrontCorner.x, leftBottomFrontCorner.y, leftBottomFrontCorner.z};
    _vertices[1] = glm::vec3{rightTopBackCorner.x, leftBottomFrontCorner.y, leftBottomFrontCorner.z};
    _vertices[2] = glm::vec3{rightTopBackCorner.x, rightTopBackCorner.y, leftBottomFrontCorner.z};
    _vertices[3] = glm::vec3{leftBottomFrontCorner.x, rightTopBackCorner.y, leftBottomFrontCorner.z};
    _vertices[4] = glm::vec3{leftBottomFrontCorner.x, leftBottomFrontCorner.y, rightTopBackCorner.z};
    _vertices[5] = glm::vec3{rightTopBackCorner.x, leftBottomFrontCorner.y, rightTopBackCorner.z};
    _vertices[6] = glm::vec3{rightTopBackCorner.x, rightTopBackCorner.y, rightTopBackCorner.z};
    _vertices[7] = glm::vec3{leftBottomFrontCorner.x, rightTopBackCorner.y, rightTopBackCorner.z};
    _modelMatrix = glm::translate(glm::mat4(1.0f), pos);
}

std::vector<Triangle> Box::GetTriangles() {
    std::vector<Triangle> triangles;
    triangles.reserve(12);
    // front wall
    triangles.push_back({_vertices[0], _vertices[1], _vertices[2], glm::vec3{0, 0, 1}});
    triangles.push_back({_vertices[2], _vertices[3], _vertices[0], glm::vec3{0, 0, 1}});
    // left wall
    triangles.push_back({_vertices[4], _vertices[0], _vertices[3], glm::vec3{-1, 0, 0}});
    triangles.push_back({_vertices[7], _vertices[4], _vertices[3], glm::vec3{-1, 0, 0}});
    // right wall
    triangles.push_back({_vertices[1], _vertices[5], _vertices[6], glm::vec3{1, 0, 0}});
    triangles.push_back({_vertices[6], _vertices[2], _vertices[1], glm::vec3{1, 0, 0}});
    // back wall
    triangles.push_back({_vertices[5], _vertices[4], _vertices[7], glm::vec3{0, 0, -1}});
    triangles.push_back({_vertices[7], _vertices[6], _vertices[5], glm::vec3{0, 0, -1}});
    // bottom
    triangles.push_back({_vertices[4], _vertices[5], _vertices[1], glm::vec3{0, -1, 0}});
    triangles.push_back({_vertices[1], _vertices[0], _vertices[4], glm::vec3{0, -1, 0}});
    // top
    triangles.push_back({_vertices[7], _vertices[3], _vertices[2], glm::vec3{0, 1, 0}});
    triangles.push_back({_vertices[2], _vertices[6], _vertices[7], glm::vec3{0, 1, 0}});
    return triangles;
}

glm::mat4 Box::GetModelMatrix() { return _modelMatrix; }