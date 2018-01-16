//
// Created by appledash on 1/12/18.
//

#ifndef GLCONI_GLCONI_H
#define GLCONI_GLCONI_H


#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include "VertexBufferObject.h"
#include "ShaderProgram.h"
#include "Cube.h"

class GLConi {
private:
    glm::vec3 bgColor;
    Cube *cube;

    void checkGLError(const char *prefix);
public:
    GLFWwindow *window;
    int windowWidth;
    int windowHeight;

    GLConi();

    ~GLConi();

    bool drawFrame();
};


#endif //GLCONI_GLCONI_H
