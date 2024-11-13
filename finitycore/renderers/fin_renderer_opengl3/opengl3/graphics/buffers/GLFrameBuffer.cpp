
#include "GLFrameBuffer.h"



#include <cstdio>
#include <iostream>


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
    glDrawBuffers(sizeof(attachments) / sizeof(attachments[0]), attachments);
}

void GLFrameBuffer::readBuffer(const GLBuffer buffer) const {
    glReadBuffer(static_cast<GLint>(buffer));
    catchErrors();
}

void GLFrameBuffer::catchErrors() const {
    const auto err = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    switch (err) {
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        std::cerr << mName << " error: Not all framebuffer attachement points are framebuffer attachements complete. " << err << '\n';
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        std::cerr << mName << " error: No images are attached to the framebuffer. " << err << '\n';
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        std::cerr << mName << " error: value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi. " << err << '\n';
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        std::cerr << mName << " error: GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER. " << err << '\n';
        break;

    case GL_FRAMEBUFFER_UNSUPPORTED:
        std::cerr << mName << " error: The combination of internal formats of the\
								 attached images violates an implementation-dependent\
								 set of restrictions. " << err << '\n';
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        std::cerr << mName << " error: the value of GL_RENDERBUFFER_SAMPLES is not the\
								 same for all attached renderbuffers, or the value of\
								 GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for\
								 all attached textures. " << err << '\n';
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
        std::cerr << mName << " error: any framebuffer attachment is layered, and any\
								 populated attachment is not layered, or if all populated\
								 color attachments are not from textures of the same target. " << err << '\n';
        break;

    default:
        break;
    }
}
