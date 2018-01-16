#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <sys/time.h>
#include "Shaders.h"
#include "GLConi.h"
#include "ShaderProgram.h"


GLFWwindow *initGL(int windowWidth, int windowHeight) {
    if (!glfwInit()) {
        throw std::runtime_error("failed to initialize glfw");
    }

    GLFWwindow *window;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight, "GLConi", nullptr, nullptr);

    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("failed to greate glfw window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(window);
        glfwTerminate();
        throw std::runtime_error("failed to initialize glew");
    }

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    return window;
}

int main() {
    GLFWwindow *window = initGL(1024, 768);

    GLConi *coni = new GLConi();
    coni->window = window;

    while (coni->drawFrame());

    glfwDestroyWindow(coni->window);

    return 0;
}