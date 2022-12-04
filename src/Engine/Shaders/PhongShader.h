#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "Shader.h"

class PhongShader : public Shader {

  public:
    PhongShader() {}
    PhongShader(const char* vertexPath, const char* fragmentPath) : Shader(vertexPath, fragmentPath) {}

    void setParamsForObject(const FrameDrawingInfo& frameDrawingInfo, const Object& object,
                            const OpenGLRendererSettings& settings) override {
        setMat4f("projection", frameDrawingInfo.projection);
        setMat4f("model", object.model);
        setMat4f("view", frameDrawingInfo.camera->getViewMatrix());
        setVec3("light.position", frameDrawingInfo.lightSource->position);
        setVec3("light.ambient", settings.lightSource.ambient);
        setVec3("light.diffuse", settings.lightSource.diffuse);
        setVec3("light.specular", settings.lightSource.specular);
        setVec3("viewPos", frameDrawingInfo.camera->position_);
        setVec3("material.ambient", settings.objectMaterial.ambient);
        setVec3("material.diffuse", settings.objectMaterial.diffuse);
        setVec3("material.specular", settings.objectMaterial.specular);
        setFloat("material.shininess", settings.objectMaterial.shininess);
    }
};

#endif