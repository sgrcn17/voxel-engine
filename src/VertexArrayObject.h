#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H

#include <glad/glad.h>
#include "VertexBufferObject.h"

class VertexArrayObject {
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VertexBufferObject& vbo, GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) const;

private:
    GLuint ID;
    void SetAttributePointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) const;
};

#endif
