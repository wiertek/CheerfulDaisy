#ifndef SIMPLESHADER_H
#define SIMPLESHADER_H

#include "Shader.h"

class SimpleShader : public Shader {

  public:
    SimpleShader() {}
    SimpleShader(const char* vertexPath, const char* fragmentPath) : Shader(vertexPath, fragmentPath) {}

    void setParamsForObject(const FrameDrawingInfo& frameDrawingInfo, const Object& object,
                            const OpenGLRendererSettings& settings) override {
        setMat4f("projection", frameDrawingInfo.projection);
        setMat4f("model", object.model);
        setMat4f("view", frameDrawingInfo.camera->getViewMatrix());
        setVec3("color", settings.objectMaterial.ambient);
    }
};

#endif