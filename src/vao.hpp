#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "vbo.hpp"

class VAO {
public:
    VAO();
    void LinkVBO(VBO vbo, GLuint layout);
    void Bind();
    void Unbind();
    void Delete();

private:
    GLuint ID;
};

#endif