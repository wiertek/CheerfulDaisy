#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "Shader.h"

class PhongShader : public Shader {
    
public:
    PhongShader() {}
    PhongShader(const char* vertexPath, const char* fragmentPath) : Shader(vertexPath, fragmentPath) {}

    void SetParamsForObject(const FrameDrawingInfo& frameDrawingInfo, const Object& object, const Camera& camera, const LightSource& ligthSource) override {
        SetMat4f("projection", frameDrawingInfo.projection);
        SetMat4f("model", object.model);
        SetMat4f("view", camera.getViewMatrix());
        SetVec3("objectColor", object.color);
        SetVec3("ligthPos", ligthSource.position);
        SetVec3("lightColor", ligthSource.color);
    }
};

#endif