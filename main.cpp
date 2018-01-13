#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <sys/time.h>
#include "Shaders.h"
#include "GLConi.h"
#include "ShaderProgram.h"


int main() {
    GLConi *coni = new GLConi();

    while (coni->drawFrame());

    return 0;
}