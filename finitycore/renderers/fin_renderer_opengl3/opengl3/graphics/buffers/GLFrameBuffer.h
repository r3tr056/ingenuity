#pragma once

#ifndef FINITY_RENDERER_GLFRAMEBUFFER_H
#define FINITY_RENDERER_GLFRAMEBUFFER_H

#include <GL/glew.h>
#include <string_view>
#include <string>

class GLFrameBuffer {

private:
    void catchErrors() const;

    GLuint mfboID{ 0 };

    std::string mName;

public:
    enum class AttachmentType : decltype(GL_COLOR_ATTACHMENT0) {
        COLOR0 = GL_COLOR_ATTACHMENT0,
        COLOR1 = GL_COLOR_ATTACHMENT1,
        COLOR2 = GL_COLOR_ATTACHMENT2,
        COLOR3 = GL_COLOR_ATTACHMENT3,
        COLOR4 = GL_COLOR_ATTACHMENT4,

        DEPTH = GL_DEPTH_ATTACHMENT,
        STENCIL = GL_STENCIL_ATTACHMENT
    };

    enum class BufferBitMasks : decltype(GL_COLOR_BUFFER_BIT) {
        COLOR = GL_COLOR_BUFFER_BIT,
        DEPTH = GL_DEPTH_BUFFER_BIT,
        STENCIL = GL_STENCIL_BUFFER_BIT
    };

    enum class GLBuffer : decltype(GL_NONE) {
        NONE = GL_NONE,
        FRONT = GL_FRONT,
        BACK = GL_BACK,
        LEFT = GL_LEFT,
        RIGHT = GL_RIGHT,
        FRONT_RIGHT = GL_FRONT_RIGHT,
        BACK_LEFT = GL_BACK_LEFT
    };

    // intialize the framebuffer with OpenGL
    void Init(std::string& name);
    // Tell opengl to delete this framebuffer and underlying attachments
    void Delete();

    // deletes and re-initialized the frame buffer.
    void Reset();

    void attachTexture(const GLuint& texID, const AttachmentType colorAttachment) const;
    void attachRenderBuffer(const GLuint& rbID, const AttachmentType attachType) const;
    void bind() const;
    void unbind() const;
    static void drawBuffers(const unsigned int attachments[]);
    void drawBuffer(GLBuffer buffer) const;
    void readBuffer(const GLBuffer buffer) const;

};

#endif //FINITY_GUI_GLFRAMEBUFFER_H
