#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class EBO {
    public:
        EBO() { glGenBuffers(1, &id); }
        ~EBO() { glDeleteBuffers(1, &id); }

        void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
        void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
        
        void setData(GLsizeiptr size, const void* data, GLenum usage) const { 
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage); 
        }

    private:
        GLuint id;
};