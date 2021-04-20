#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <glm/glm.hpp>
#include <array>

struct Triangle {
    std::array<glm::vec3, 3> vertices;
    glm::vec3 normal;
};

struct Object {
    unsigned int VBO; 
    unsigned int VAO; 
    size_t verticesNum;
    glm::mat4 model{ glm::mat4(1.0f) };
    glm::vec3 color;
};

struct FrameDrawingInfo {
    glm::mat4 projection;
};


#endif