#include "Box.h"

Box::Box(glm::vec3 from, glm::vec3 to) {
    _vertices[0] = glm::vec3{from.x, from.y, from.z};
    _vertices[1] = glm::vec3{from.x, from.y, to.z};
    _vertices[2] = glm::vec3{from.x, to.y, from.z};
    _vertices[3] = glm::vec3{from.x, to.y, to.z};
    _vertices[4] = glm::vec3{to.x, from.y, from.z};
    _vertices[5] = glm::vec3{to.x, from.y, to.z};
    _vertices[6] = glm::vec3{to.x, to.y, from.z};
    _vertices[7] = glm::vec3{to.x, to.y, to.z};
}

std::vector<Triangle> Box::GetTriangles() {
    std::vector<Triangle> triangles;
    triangles.reserve(12);
    //left wall
    triangles.push_back({_vertices[0], _vertices[1], _vertices[2]});
    triangles.push_back({_vertices[1], _vertices[2], _vertices[3]});
    //front wall
    triangles.push_back({_vertices[0], _vertices[2], _vertices[6]});
    triangles.push_back({_vertices[0], _vertices[4], _vertices[6]});
    //right wall
    triangles.push_back({_vertices[4], _vertices[5], _vertices[6]});
    triangles.push_back({_vertices[5], _vertices[6], _vertices[7]});
    //back wall
    triangles.push_back({_vertices[1], _vertices[5], _vertices[7]});
    triangles.push_back({_vertices[1], _vertices[3], _vertices[5]});
    //bottom
    triangles.push_back({_vertices[0], _vertices[1], _vertices[4]});
    triangles.push_back({_vertices[1], _vertices[4], _vertices[5]});
    //top
    triangles.push_back({_vertices[2], _vertices[3], _vertices[6]});
    triangles.push_back({_vertices[3], _vertices[6], _vertices[7]});
    return triangles;
}