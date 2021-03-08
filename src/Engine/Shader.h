#ifndef SHADER_H
#define SHADER_H

#include "../Common/OpenGL.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader() {}
    Shader::Shader(const char* vertexPath, const char* fragmentPath);

    void Use() 
    { 
        glUseProgram(_id); 
    }

    void SetMat4f(const std::string &name, glm::mat4 matrix) const
    {         
        glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix)); 
    }

private:
    void CheckCompileErrors(unsigned int shader, const char* type);
    void CheckLinkageErrors(unsigned int shader, const char* type);

    unsigned int _id;
};

#endif