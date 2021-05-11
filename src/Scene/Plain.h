#ifndef PLAIN_H
#define PLAIN_H

#include <array>
#include <glm/glm.hpp>

#include "Primitive.h"
#include <vector>

class Plain : public Primitive {

  private:
    std::array<glm::vec3, 4> _vertices;
    glm::mat4 _modelMatrix;

  public:
    Plain(glm::vec3 from, float yLevel, glm::vec3 to);
    std::vector<Triangle> GetTriangles() override;
    glm::mat4 GetModelMatrix() override;
    std::vector<float> GetVerticesWithCoords();
    std::vector<int> GetIndices();
};

#endif
