//
// Created by appledash on 1/12/18.
//

#include <GL/glew.h>
#include "Shaders.h"

/**
 * Read the contents of the file at the given path.
 * @param path
 * @param outData
 * @return
 */
int readFile(const char *path, char **outData) {
    FILE *fp = fopen(path, "r");
    long fileSize;
    char *dataBuf;

    if (!fp) {
        fprintf(stderr, "readFile(): failed to open \"%s\" for reading.\n", path);
        return -1;
    }

    fseek(fp, 0, SEEK_END);

    fileSize = ftell(fp);

    if (fileSize > SIZE_MAX || fileSize > INT32_MAX) { // Hey, you never know.
        fprintf(stderr, "readFile(): file size of \"%s\" > SIZE_MAX or > INT32_MAX. WTF?\n", path);
        fclose(fp);
        return -1;
    }

    dataBuf = (char *)calloc(1, (size_t) fileSize + 1);

    rewind(fp);

    if (fread(dataBuf, (size_t) fileSize, 1, fp) != 1) {
        fprintf(stderr, "readFile(): failed to read %d bytes from \"%s\".\n", (int) fileSize, path);
        fclose(fp);
        free(dataBuf);
        return -1;
    }

    fclose(fp);

    *outData = dataBuf;

    return (int) fileSize;
}

GLuint Shaders::loadShader(const char *path, GLenum type) {
    GLuint shaderId = glCreateShader(type);
    char *shaderData;
    GLint result = GL_FALSE;
    GLsizei infoLogLength;

    if (readFile(path, &shaderData) == -1) {
        fprintf(stderr, "loadShader(): failed to load \"%s\".\n", path);
        return 0;
    }

    glShaderSource(shaderId, 1, (const char **) &shaderData, nullptr);
    glCompileShader(shaderId);

    free(shaderData);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
        char *shaderErrorMessage = (char *) calloc(1, infoLogLength + 1);
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, shaderErrorMessage);

        fprintf(stderr, "loadVertexShader():\n%s\n", shaderErrorMessage);
        free(shaderErrorMessage);
        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}


GLuint Shaders::loadShaders(const char *vertPath, const char *fragPath) {
    GLuint vertId, fragId;
    GLuint programId;
    GLint result = GL_FALSE;
    GLsizei infoLogLength;

    if ((vertId = Shaders::loadShader(vertPath, GL_VERTEX_SHADER)) == 0) {
        fprintf(stderr, "loadShaders(): failed to load vertex shader \"%s\"\n", vertPath);
        return 0;
    }

    if ((fragId = Shaders::loadShader(fragPath, GL_FRAGMENT_SHADER)) == 0) {
        fprintf(stderr, "loadShaders(): failed to load fragment shader \"%s\"\n", fragPath);
        return 0;
    }

    programId = glCreateProgram();
    glAttachShader(programId, vertId);
    glAttachShader(programId, fragId);
    glLinkProgram(programId);

    glDetachShader(programId, vertId);
    glDetachShader(programId, fragId);
    glDeleteShader(vertId);
    glDeleteShader(fragId);

    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
        char *shaderErrorMessage = (char *) calloc(1, infoLogLength + 1);
        glGetProgramInfoLog(programId, infoLogLength, nullptr, shaderErrorMessage);

        fprintf(stderr, "loadShaders():\n%s\n", shaderErrorMessage);
        free(shaderErrorMessage);

        glDeleteProgram(programId);

        return 0;
    }

    return programId;
}

