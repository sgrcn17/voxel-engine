#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vbo.hpp"

class VAO {
    public:
        VAO() { glGenVertexArrays(1, &id); }
        ~VAO() { glDeleteVertexArrays(1, &id); }

        void bind() const { glBindVertexArray(id); }
        void unbind() const { glBindVertexArray(0); }
        
        void linkAttrib(GLuint layout, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
            glVertexAttribPointer(layout, size, type, normalized, stride, offset);
            glEnableVertexAttribArray(layout);
        }

    private: 
        GLuint id;
};