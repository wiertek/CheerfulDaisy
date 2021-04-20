#ifndef SIMPLESHADER_H
#define SIMPLESHADER_H

#include "Shader.h"

class SimpleShader : public Shader {
    
public:
    SimpleShader() {}
    SimpleShader(const char* vertexPath, const char* fragmentPath) : Shader(vertexPath, fragmentPath) {}

    void SetParamsForObject(const FrameDrawingInfo& frameDrawingInfo, const Object& object, const Camera& camera, const LightSource& ligthSource) override {
        SetMat4f("projection", frameDrawingInfo.projection);
        SetMat4f("model", object.model);
        SetMat4f("view", camera.getViewMatrix());
        SetVec3("color", object.color);
    }
};

#endif