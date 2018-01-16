//
// Created by appledash on 1/12/18.
//

#ifndef GLCONI_VERTEXBUFFEROBJECT_H
#define GLCONI_VERTEXBUFFEROBJECT_H


#include <GL/gl.h>
#include <GL/glew.h>

class VertexBufferObject {
private:
    GLuint vboId;
    GLuint index;
public:
    VertexBufferObject(GLuint index);
    ~VertexBufferObject();
    void bind();
    void unbind();
    void putVertices(float *data, int dataLength);
};


#endif //GLCONI_VERTEXBUFFEROBJECT_H
