#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &ID);
    Bind();
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &ID);
}

void VertexArrayObject::Bind() const {
    glBindVertexArray(ID);
}

void VertexArrayObject::Unbind() const {
    glBindVertexArray(0);
}

void VertexArrayObject::AddBuffer(const VertexBufferObject& vbo, GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) const {
    vbo.Bind();
    SetAttributePointer(index, size, type, stride, pointer);
    vbo.Unbind();
}

void VertexArrayObject::SetAttributePointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) const {
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
}
