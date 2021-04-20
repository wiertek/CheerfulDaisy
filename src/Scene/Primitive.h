#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../Common/Definitions.h"
#include <vector>

constexpr auto DEFAULT_OBJECT_COLOR = glm::vec3(0.96f, 0.51f, 0.26f);

class Primitive {
public:
    virtual std::vector<Triangle> GetTriangles() = 0;
    virtual ~Primitive() {}

    Primitive& SetColor(glm::vec3 colorArg) {
        this->color = colorArg;
        return *this;
    }

    glm::vec3 color = DEFAULT_OBJECT_COLOR;
};

#endif
