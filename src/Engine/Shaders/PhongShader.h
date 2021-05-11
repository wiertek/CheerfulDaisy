#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "Shader.h"

class PhongShader : public Shader {

  public:
    PhongShader() {}
    PhongShader(const char* vertexPath, const char* fragmentPath) : Shader(vertexPath, fragmentPath) {}

    void SetParamsForObject(const FrameDrawingInfo& frameDrawingInfo, const Object& object,
                            const OpenGLRendererSettings& settings) override {
        SetMat4f("projection", frameDrawingInfo.projection);
        SetMat4f("model", object.model);
        SetMat4f("view", frameDrawingInfo.camera->getViewMatrix());
        SetVec3("light.position", frameDrawingInfo.lightSource->position);
        SetVec3("light.ambient", settings.lightSource.ambient);
        SetVec3("light.diffuse", settings.lightSource.diffuse);
        SetVec3("light.specular", settings.lightSource.specular);
        SetVec3("viewPos", frameDrawingInfo.camera->position);
        SetVec3("material.ambient", settings.objectMaterial.ambient);
        SetVec3("material.diffuse", settings.objectMaterial.diffuse);
        SetVec3("material.specular", settings.objectMaterial.specular);
        SetFloat("material.shininess", settings.objectMaterial.shininess);
    }
};

#endif