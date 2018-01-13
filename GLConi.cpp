//
// Created by appledash on 1/12/18.
//

#include <GL/glew.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <sys/time.h>
#include <iostream>
#include "GLConi.h"
#include "Shaders.h"

long long milliTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}

void GLConi::checkGLError(const char *prefix) {
    GLenum err = glGetError();

    if (err != GL_NO_ERROR) {
        const char *str =  (const char *) glewGetErrorString(err);

        fprintf(stderr, "GL ERROR: [%s] %s (%d)\n", prefix, str, err);
    }
}


bool GLConi::drawFrame() {
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->triangleShader->use();

    float angle = (float)((milliTime() / 10) % 360);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) this->windowWidth / (float) this->windowHeight, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(4, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::rotate(glm::radians(angle), glm::vec3(0, 1, 0)) * glm::mat4(1.0f);

    glm::mat4 mvp = proj * view * model;

    glUniformMatrix4fv(this->triangleShader->getUniformLocation("MVP"), 1, GL_FALSE, &mvp[0][0]);

    this->triangleVbo->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    this->triangleVbo->unbind();

    glfwSwapBuffers(this->window);
    glfwPollEvents();


    return glfwGetKey(this->window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(this->window);
}

void GLConi::initGL() {

    if (!glfwInit()) {
        throw std::runtime_error("failed to initialize glfw");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, "GLConi", nullptr, nullptr);

    if (this->window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("failed to greate glfw window");
    }

    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(this->window);
        glfwTerminate();
        throw std::runtime_error("failed to initialize glew");
    }

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    this->triangleVbo = new VertexBufferObject();

    this->triangleShader = new ShaderProgram("shaders/triangle");

    float triangle[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
    };

    this->triangleVbo->putVertices(&triangle[0], sizeof(triangle));
}

