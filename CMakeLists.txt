cmake_minimum_required(VERSION 3.10)
project(glconi)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLIDE_DIRS})

add_executable(glconi main.cpp Shaders.cpp Shaders.h GLConi.cpp GLConi.h VertexBufferObject.cpp VertexBufferObject.h ShaderProgram.cpp ShaderProgram.h)

target_link_libraries(glconi ${GLEW_LIBRARIES})
target_link_libraries(glconi ${OPENGL_gl_LIBRARY} glfw)
