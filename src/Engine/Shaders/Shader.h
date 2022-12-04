#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "../../Common/Definitions.h"
#include "../../Common/OpenGL.h"
#include "../../Scene/Scene.h"
#include "../Camera.h"
#include "../OpenGLRendererSettings.h"

class Shader {
  public:
    Shader() {}
    Shader(const char* vertexPath, const char* fragmentPath);

    virtual void setParamsForObject(const FrameDrawingInfo& frameDrawingInfo, const Object& object,
                                    const OpenGLRendererSettings& settings) = 0;

    void use() { glUseProgram(id_); }

    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
    }

    void setVec3(const std::string& name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
    }

    void setMat4f(const std::string& name, glm::mat4 matrix) const {
        glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

  private:
    void checkCompileErrors(unsigned int shader, const char* type);
    void checkLinkageErrors(unsigned int shader, const char* type);

    unsigned int id_;
};

#endif