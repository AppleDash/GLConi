//
// Created by appledash on 1/12/18.
//

#ifndef GLCONI_GLCONI_H
#define GLCONI_GLCONI_H


#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include "VertexBufferObject.h"
#include "ShaderProgram.h"

class GLConi {
private:
    int windowWidth;
    int windowHeight;
    GLFWwindow *window;
    glm::vec3 bgColor;
    ShaderProgram *triangleShader;
    VertexBufferObject *triangleVbo;

    void checkGLError(const char *prefix);
public:
    GLConi() : windowWidth(1024), windowHeight(768), bgColor(0.0f, 0.0f, 0.4f) {
        this->initGL();
    }

    void initGL();
    bool drawFrame();
};


#endif //GLCONI_GLCONI_H
