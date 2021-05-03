#ifndef PLAIN_H
#define PLAIN_H

#include <array>
#include <glm/glm.hpp>

#include "Primitive.h"
#include <vector>


class Plain : public Primitive {
    
private:
    std::array<glm::vec3, 4> _vertices;

public:
    Plain(glm::vec3 from, glm::vec3 to);
    std::vector<Triangle> GetTriangles() override;
    std::vector<float> GetVerticesWithCoords();
    std::vector<int> GetIndices();
};

#endif
