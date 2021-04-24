#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <array>
#include <glm/glm.hpp>


struct LightSource {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct Triangle {
    std::array<glm::vec3, 3> vertices;
    glm::vec3 normal;
};

struct Object {
    unsigned int VBO;
    unsigned int VAO;
    size_t verticesNum;
    glm::mat4 model{glm::mat4(1.0f)};
};

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

struct FrameDrawingInfo {
    glm::mat4 projection;
    Material material;
};

#endif