
#include "glVertexArray.h"

void GLVertexArray::init() noexcept {
    glGenVertexArrays(1, &mVAO);
}

void GLVertexArray::attachBuffer(
    const BufferType type,
    const GLsizeiptr size,
    const DrawMode mode,
    const void *data
) noexcept {

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(type, buffer);
    glBufferData(type, size, data, mode);
}

void GLVertexArray::bind() const noexcept {
    glBindVertexArray(mVAO);
}

void GLVertexArray::Delete() noexcept {
    glDeleteVertexArrays(1, &mVAO);
}

void GLVertexArray::enableAttribute(const GLuint index, const GLint size, const GLsizei offset,
                                    const void *data) noexcept {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, offset, data);
}