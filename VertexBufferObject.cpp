//
// Created by appledash on 1/12/18.
//

#include <GL/glew.h>
#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject() {
    glGenBuffers(1, &(this->vboId));
}

VertexBufferObject::~VertexBufferObject() {
    glDeleteBuffers(1, &(this->vboId));
}


void VertexBufferObject::bind() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Attribute index 0 in the shader, 3 floats per vertex
}

void VertexBufferObject::unbind() {
    glDisableVertexAttribArray(0);
}

void VertexBufferObject::putVertices(float *data, int dataLength) {
    glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
    glBufferData(GL_ARRAY_BUFFER, dataLength, data, GL_STATIC_DRAW);
}
