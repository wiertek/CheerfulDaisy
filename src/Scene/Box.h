#ifndef BOX_H
#define BOX_H

#include <array>
#include <glm/glm.hpp>

#include "Primitive.h"
#include <vector>


class Box : public Primitive {
    
private:
    std::array<glm::vec3, 8> _vertices;
    glm::mat4 _modelMatrix;

public:
    Box(glm::vec3 from, glm::vec3 to);
    std::vector<Triangle> GetTriangles() override;
    glm::mat4 GetModelMatrix() override;
};

#endif
