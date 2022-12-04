#include "Shader.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode, fragmentCode;
    std::ifstream vShaderFile, fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cout << "Cannot read the shader file." << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    id_ = glCreateProgram();
    glAttachShader(id_, vertex);
    glAttachShader(id_, fragment);
    glLinkProgram(id_);
    checkLinkageErrors(id_, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::checkCompileErrors(unsigned int shader, const char* type) {
    int success;
    char infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                  << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}

void Shader::checkLinkageErrors(unsigned int shader, const char* type) {
    int success;
    char infoLog[1024];
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                  << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}