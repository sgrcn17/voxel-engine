#ifndef VERTEX_BUFFER_OBJECT_H
#define VERTEX_BUFFER_OBJECT_H

#include <glad/glad.h>

class VertexBufferObject {
public:
    VertexBufferObject(const void* data, GLsizei size);
    ~VertexBufferObject();

    void Bind() const;
    void Unbind() const;
    void SetData(const void* data, GLsizei size);

    void SetAttributePointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) const;

private:
    GLuint ID;
};

#endif
