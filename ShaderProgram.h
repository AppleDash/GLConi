//
// Created by appledash on 1/12/18.
//

#ifndef GLCONI_SHADERPROGRAM_H
#define GLCONI_SHADERPROGRAM_H


#include <GL/gl.h>
#include <GL/glew.h>

class ShaderProgram {
private:
    GLuint programId;
public:
    ShaderProgram(const char *name);
    ShaderProgram(const char *vertexPath, const char *fragmentPath);
    ~ShaderProgram();
    void use();
    GLint getUniformLocation(const char *name);
};


#endif //GLCONI_SHADERPROGRAM_H
