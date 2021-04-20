#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Common/OpenGL.h"
#include "../Camera.h"
#include "../../Common/Definitions.h"
#include "../../Scene/Scene.h"

class Shader
{
public:
    Shader() {}
    Shader(const char* vertexPath, const char* fragmentPath);

    virtual void SetParamsForObject(const FrameDrawingInfo& frameDrawingInfo, const Object& object, const Camera& camera, const LightSource& lightSource) = 0;

    void Use() 
    { 
        glUseProgram(_id); 
    }

    void SetVec3(const std::string& name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]); 
    }

    void SetMat4f(const std::string& name, glm::mat4 matrix) const
    {         
        glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix)); 
    }

private:
    void CheckCompileErrors(unsigned int shader, const char* type);
    void CheckLinkageErrors(unsigned int shader, const char* type);

    unsigned int _id;
};

#endif