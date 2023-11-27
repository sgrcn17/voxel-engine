#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(const void* data, GLsizei size) {
    glGenBuffers(1, &ID);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject() {
    glDeleteBuffers(1, &ID);
}

void VertexBufferObject::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBufferObject::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::SetData(const void* data, GLsizei size) {
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    Unbind();
}

void VertexBufferObject::SetAttributePointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) const {
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
}
