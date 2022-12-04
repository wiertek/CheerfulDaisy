#ifndef PLAIN_H
#define PLAIN_H

#include <array>
#include <glm/glm.hpp>

#include "Primitive.h"
#include <vector>

class Plain : public Primitive {

  private:
    std::array<glm::vec3, 4> vertices_;
    glm::mat4 modelMatrix_;

  public:
    Plain(glm::vec3 from, float yLevel, glm::vec3 to);
    std::vector<Triangle> getTriangles() override;
    glm::mat4 getModelMatrix() override;
    std::vector<float> getVerticesWithCoords();
    std::vector<int> getIndices();
};

#endif
