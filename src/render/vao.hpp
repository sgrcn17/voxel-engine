#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "vbo.hpp"

class VAO {
public:
    VAO();
    void LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();

private:
    GLuint ID;
};

#endif