//
// Created by appledash on 1/12/18.
//

#ifndef GLCONI_SHADERPROGRAM_H
#define GLCONI_SHADERPROGRAM_H


#include <GL/gl.h>
#include <GL/glew.h>
#include "VertexBufferObject.h"

class ShaderProgram {
private:
    VertexBufferObject *vbos[10];
    GLuint programId;
public:
    ShaderProgram(const char *name);
    ShaderProgram(const char *vertexPath, const char *fragmentPath);
    ~ShaderProgram();
    VertexBufferObject *operator[] (const unsigned int &i) {
        if (this->vbos[i] == nullptr) {
            this->vbos[i] = new VertexBufferObject(i);
        }

        return this->vbos[i];
    }
    void use();
    void unuse();
    GLint getUniformLocation(const char *name);
    void uniformMatrix4fv(const char *location, GLsizei count, GLfloat *ptr);
};


#endif //GLCONI_SHADERPROGRAM_H
