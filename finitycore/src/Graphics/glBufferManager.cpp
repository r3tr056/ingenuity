
#include "glBufferManager.h"

void GLVertexIndexBuffer::createBuffers(const std::vector<VertexHolder> &vertices, const std::vector<unsigned int> &indices) {

    // Allocate and assign a Vertex Array Object to out graphics handle
    glGenVertexArrays(1, &mVAO);
    // Allocate and assign 1 vertex array object to our handle
    glGenBuffers(1, &mVBO);
    // Allocate and assing 1 index buffer object to our handle
    glGenBuffers(1, &mEBO);
    // Bind the vertex array object as  the current target for drawing
    glBindVertexArray(mVAO);
    // Bind our first vertex buffer object as beign the active buffer and storing vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    // Copy the vertex data from triangle to our buffer
    // vertices.size() * sizeof(GLfloat) is the size of the vertex object
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size()*sizeof(GLfloat)), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(vertices.size()*sizeof(GLuint)), indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexHolder), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexHolder), (void*) offsetof(VertexHolder, mNormal));

    glBindVertexArray(0);
}

void GLVertexIndexBuffer::deleteBuffers() {
    // Cleanup  all the things we bound and allocated to the GL context
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &mEBO);
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}

void GLVertexIndexBuffer::bind() {
    glBindVertexArray(mVAO);
}

void GLVertexIndexBuffer::unbind() {
    glBindVertexArray(0);
}

void GLVertexIndexBuffer::draw(int index_count) {
    bind();
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
    unbind();
}

void GLFrameBuffer::createBuffers(int32_t width, int32_t height) {
    mWidth = width;
    mHeight = height;

    if (mFBO)
        deleteBuffers();

    glGenFramebuffers(1, &mFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glCreateTextures(GL_TEXTURE_2D, 1, &mTexId);
    glBindTexture(GL_TEXTURE_2D, mTexId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexId, 0);

    GLenum buffers[4] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers((GLsizei)mTexId, buffers);

    unbind();
}

void GLFrameBuffer::deleteBuffers() {
    if (mFBO) {
        glDeleteFramebuffers(GL_FRAMEBUFFER, &mFBO);
        glDeleteTextures(1, &mTexId);
        glDeleteTextures(1, &mDepthId);
    }
}

void GLFrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glViewport(0, 0, mWidth, mHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLFrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint GLFrameBuffer::getTexture() {
    return mTexId;
}