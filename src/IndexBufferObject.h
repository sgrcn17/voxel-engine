#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class IndexBufferObject {
public:
    IndexBufferObject(const GLuint* data, GLsizei count);
    ~IndexBufferObject();
    
    void Bind() const;
    void Unbind() const;
    
    GLsizei GetCount() const;

private:
    GLuint ID;
    GLsizei count;
};
