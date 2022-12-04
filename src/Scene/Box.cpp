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
    vertices_[0] = glm::vec3{leftBottomFrontCorner.x, leftBottomFrontCorner.y, leftBottomFrontCorner.z};
    vertices_[1] = glm::vec3{rightTopBackCorner.x, leftBottomFrontCorner.y, leftBottomFrontCorner.z};
    vertices_[2] = glm::vec3{rightTopBackCorner.x, rightTopBackCorner.y, leftBottomFrontCorner.z};
    vertices_[3] = glm::vec3{leftBottomFrontCorner.x, rightTopBackCorner.y, leftBottomFrontCorner.z};
    vertices_[4] = glm::vec3{leftBottomFrontCorner.x, leftBottomFrontCorner.y, rightTopBackCorner.z};
    vertices_[5] = glm::vec3{rightTopBackCorner.x, leftBottomFrontCorner.y, rightTopBackCorner.z};
    vertices_[6] = glm::vec3{rightTopBackCorner.x, rightTopBackCorner.y, rightTopBackCorner.z};
    vertices_[7] = glm::vec3{leftBottomFrontCorner.x, rightTopBackCorner.y, rightTopBackCorner.z};
    modelMatrix_ = glm::translate(glm::mat4(1.0f), pos);
}

std::vector<Triangle> Box::getTriangles() {
    std::vector<Triangle> triangles;
    triangles.reserve(12);
    // front wall
    triangles.push_back({{vertices_[0], vertices_[1], vertices_[2]}, glm::vec3{0, 0, 1}});
    triangles.push_back({{vertices_[2], vertices_[3], vertices_[0]}, glm::vec3{0, 0, 1}});
    // left wall
    triangles.push_back({{vertices_[4], vertices_[0], vertices_[3]}, glm::vec3{-1, 0, 0}});
    triangles.push_back({{vertices_[7], vertices_[4], vertices_[3]}, glm::vec3{-1, 0, 0}});
    // right wall
    triangles.push_back({{vertices_[1], vertices_[5], vertices_[6]}, glm::vec3{1, 0, 0}});
    triangles.push_back({{vertices_[6], vertices_[2], vertices_[1]}, glm::vec3{1, 0, 0}});
    // back wall
    triangles.push_back({{vertices_[5], vertices_[4], vertices_[7]}, glm::vec3{0, 0, -1}});
    triangles.push_back({{vertices_[7], vertices_[6], vertices_[5]}, glm::vec3{0, 0, -1}});
    // bottom
    triangles.push_back({{vertices_[4], vertices_[5], vertices_[1]}, glm::vec3{0, -1, 0}});
    triangles.push_back({{vertices_[1], vertices_[0], vertices_[4]}, glm::vec3{0, -1, 0}});
    // top
    triangles.push_back({{vertices_[7], vertices_[3], vertices_[2]}, glm::vec3{0, 1, 0}});
    triangles.push_back({{vertices_[2], vertices_[6], vertices_[7]}, glm::vec3{0, 1, 0}});
    return triangles;
}

glm::mat4 Box::getModelMatrix() { return modelMatrix_; }