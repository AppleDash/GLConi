//
// Created by appledash on 1/12/18.
//

#include <GL/glew.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <sys/time.h>
#include "GLConi.h"
#include "Shaders.h"
#include "Cube.h"

long long milliTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}

GLConi::GLConi() : windowWidth(1024), windowHeight(768), bgColor(0.0f, 0.0f, 0.4f) {
    this->cube = new Cube();
}

GLConi::~GLConi() {
    delete this->cube;
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

    float angle = (float)((milliTime() / 10) % 360);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) this->windowWidth / (float) this->windowHeight, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(4, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::rotate(glm::radians(20.0f), glm::vec3(0, 0, 1)) * glm::rotate(glm::radians(angle), glm::vec3(0, 1, 0)) * this->cube->computeModel(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    this->cube->render(proj * view * model);

    glfwSwapBuffers(this->window);
    glfwPollEvents();

    this->checkGLError("???");

    return glfwGetKey(this->window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(this->window);
}
