//
// Created by appledash on 1/13/18.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include "Cube.h"

glm::mat4 Cube::computeModel(glm::vec3 start, glm::vec3 end) {
    return glm::scale(end - start);
}

void Cube::render(glm::mat4 mvp) {
    this->shader.use();

    this->shader.uniformMatrix4fv("MVP", 1, &mvp[0][0]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    this->shader[1]->putVertices(this->fillColors, sizeof(this->fillColors));
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    this->shader[1]->putVertices(this->outlineColors, sizeof(this->fillColors));
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    this->shader.unuse();
}
