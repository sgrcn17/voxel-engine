#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class EBO {
public:
    EBO(GLuint* indices, GLsizeiptr size);
    void Bind();
    void Unbind();
    void Delete();

private:
    GLuint ID;
};

#endif