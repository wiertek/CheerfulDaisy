#include "Plain.h"

Plain::Plain(glm::vec3 from, glm::vec3 to) {
    _vertices[0] = glm::vec3{from.x, 0.0f, from.z};
    _vertices[1] = glm::vec3{from.x, 0.0f, to.z};
    _vertices[2] = glm::vec3{to.x, 0.0f, to.z};
    _vertices[3] = glm::vec3{to.x, 0.0f, from.z};
}

std::vector<Triangle> Plain::GetTriangles() {
    std::vector<Triangle> triangles;
    triangles.reserve(2);
    triangles.push_back({_vertices[0], _vertices[1], _vertices[2], glm::vec3{0, 0, 1}});
    triangles.push_back({_vertices[2], _vertices[3], _vertices[0], glm::vec3{0, 0, 1}});
    return triangles;
}

std::vector<float> Plain::GetVerticesWithCoords() {
    std::vector<float> verticesAndCoords;
    verticesAndCoords.reserve(4 * ( 3 + 2));
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

std::vector<int> Plain::GetIndices() {
    return {0, 1, 3, 1, 2, 3};
}