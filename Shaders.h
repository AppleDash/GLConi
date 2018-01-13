#ifndef GLCONI_SHADERS_H
#define GLCONI_SHADERS_H
#include <GL/gl.h>
#include <GL/glew.h>
#include <fstream>

class Shaders {
public:
    static GLuint loadShader(const char *path, GLenum type);
    static GLuint loadShaders(const char *vertPath, const char *fragPath);
};


#endif // GLCONI_SHADERS_H
