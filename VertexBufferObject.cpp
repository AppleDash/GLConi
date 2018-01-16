//
// Created by appledash on 1/12/18.
//

#include <GL/glew.h>
#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(GLuint index) : index(index) {
    glGenBuffers(1, &(this->vboId));
}

VertexBufferObject::~VertexBufferObject() {
    glDeleteBuffers(1, &(this->vboId));
}

void VertexBufferObject::bind() {
    glEnableVertexAttribArray(this->index);
}

void VertexBufferObject::unbind() {
    glDisableVertexAttribArray(this->index);
}

void VertexBufferObject::putVertices(float *data, int dataLength) {
    glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
    glBufferData(GL_ARRAY_BUFFER, dataLength, data, GL_STATIC_DRAW);
    glVertexAttribPointer(this->index, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Attribute index 0 in the shader, 3 floats per vertex
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
