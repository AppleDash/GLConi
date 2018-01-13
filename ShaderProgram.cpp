//
// Created by appledash on 1/12/18.
//

#include <GL/glew.h>
#include <cstring>
#include "ShaderProgram.h"
#include "Shaders.h"

ShaderProgram::ShaderProgram(const char *name) {
    const char *vertexName = "vert.glsl";
    const char *fragmentName = "frag.glsl";
    const char *separator = "/";

    char *vertexPath = (char *)calloc(1, strlen(name) + strlen(separator) + strlen(vertexName) + 1);
    char *fragmentPath = (char *)calloc(1, strlen(name) + strlen(separator) + strlen(fragmentName) + 1);

    sprintf(vertexPath, "%s%s%s", name, separator, vertexName);
    sprintf(fragmentPath, "%s%s%s", name, separator, fragmentName);

    this->programId = Shaders::loadShaders(vertexPath, fragmentPath);

    free(vertexPath);
    free(fragmentPath);

    if (this->programId == 0) {
        throw std::runtime_error("failed to compile shader program");
    }
}


ShaderProgram::ShaderProgram(const char *vertexPath, const char *fragmentPath) {
    this->programId = Shaders::loadShaders(vertexPath, fragmentPath);
    if (this->programId == 0) {
        throw std::runtime_error("failed to compile shader program");
    }
}

void ShaderProgram::use() {
    glUseProgram(this->programId);
}

ShaderProgram::~ShaderProgram() {
    if (this->programId != 0) {
        glDeleteShader(this->programId);
    }
}

GLint ShaderProgram::getUniformLocation(const char *name) {
    return glGetUniformLocation(this->programId, name);
}
