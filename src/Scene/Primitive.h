#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <vector>

#include "../Common/Definitions.h"

class Primitive {
  public:
    virtual ~Primitive() {}

    virtual std::vector<Triangle> getTriangles() = 0;
    virtual glm::mat4 getModelMatrix() = 0;
};

#endif
