
#include "GLFrameBuffer.h"

#include <cstdio>

// Add the namespace

void GLFrameBuffer::Init(std::string& name) {
    mName = name;
    Reset();
}

void GLFrameBuffer::Reset() {
    Delete();
    glGenFramebuffers(1, &mfboID);
    catchErrors();
}

void GLFrameBuffer::Delete() {
    if (mfboID) {
        glDeleteFramebuffers(1, &mfboID);
        mfboID = 0;
    }
}

void GLFrameBuffer::attachTexture(const GLuint &texID, const AttachmentType colorAttachment) const {
    glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<GLint>(colorAttachment), GL_TEXTURE_2D, texID, 0);
    catchErrors();
}

void GLFrameBuffer::attachRenderBuffer(const GLuint &rbID, const AttachmentType attachType) const {
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLint>(attachType), GL_RENDERBUFFER, rbID);
    catchErrors();
}

void GLFrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, mfboID);
    catchErrors();
}

void GLFrameBuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    catchErrors();
}

void GLFrameBuffer::drawBuffer(const GLBuffer buffer) const {
    glDrawBuffer(static_cast<GLint>(buffer));
    catchErrors();
}

void GLFrameBuffer::drawBuffers(const unsigned int attachments[]) {
    glDrawBuffers((sizeof(&attachments) / sizeof(attachments[0])), attachments);
}

void GLFrameBuffer::readBuffer(const GLBuffer buffer) const {
    glReadBuffer(static_cast<GLint>(buffer));
    catchErrors();
}