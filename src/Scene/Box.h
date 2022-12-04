#ifndef BOX_H
#define BOX_H

#include <array>
#include <vector>

#include <glm/glm.hpp>

#include "Primitive.h"

class Box : public Primitive {

  private:
    std::array<glm::vec3, 8> vertices_;
    glm::mat4 modelMatrix_;

  public:
    Box(glm::vec3 from, glm::vec3 to);
    std::vector<Triangle> getTriangles() override;
    glm::mat4 getModelMatrix() override;
};

#endif
