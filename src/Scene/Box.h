#ifndef BOX_H
#define BOX_H

#include <array>
#include <glm/glm.hpp>

#include "Primitive.h"
#include <vector>


class Box : public Primitive {
    
private:
    std::array<glm::vec3, 8> _vertices;

public:
    Box(glm::vec3 from, glm::vec3 to);
    std::vector<Triangle> GetTriangles() override;
};

#endif
