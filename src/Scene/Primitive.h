#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../Common/Definitions.h"
#include <vector>

class Primitive {
public:
    virtual std::vector<Triangle> GetTriangles() = 0;
    virtual glm::mat4 GetModelMatrix() = 0;
    virtual ~Primitive() {}
};

#endif
