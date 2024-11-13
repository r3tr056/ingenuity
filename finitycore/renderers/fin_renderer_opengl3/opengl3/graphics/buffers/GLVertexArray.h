#pragma once


#ifndef FINITY_GL_RENDERER_VERTEXARRAY_H
#define FINITY_GL_RENDERER_VERTEXARRAY_H

#include <GL/glew.h>

class GLVertexArray {

private:
    GLuint mVAO{0};

public:
    enum BufferType : int {
        ARRAY = GL_ARRAY_BUFFER,
        ELEMENT = GL_ELEMENT_ARRAY_BUFFER
    };

    enum DrawMode : int {
        STATIC = GL_STATIC_DRAW,
        DYNAMIC = GL_DYNAMIC_DRAW,
        STREAM = GL_STREAM_DRAW
    };

    void init() noexcept;
    void attachBuffer(const BufferType type, const GLsizeiptr size, const DrawMode mode, const void *data) noexcept;
    void bind() const noexcept;
    void enableAttribute(const GLuint index, const GLint size, const GLsizei offset, const void *data) noexcept;
    void Delete() noexcept;

};

#endif //FINITY_GUI_GLVERTEXARRAY_H