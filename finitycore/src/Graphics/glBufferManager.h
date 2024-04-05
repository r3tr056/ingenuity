#ifndef FINITY_GUI_GLBUFFERMANAGER_H
#define FINITY_GUI_GLBUFFERMANAGER_H

#include "finPch.h"
// TODO : replace relative paths with references
#include "components/VertexHolder.h"
#include "renderBase.h"

// TODO : Create a more general class of VertexIndexBuffer
class GLVertexIndexBuffer : public VertexIndexBuffer
{
public:
    GLVertexIndexBuffer() : VertexIndexBuffer() {}
    void createBuffers(const std::vector<VertexHolder>& vertices, const std::vector<GLuint> &indices) override;
    void deleteBuffers() override;
    void bind() override;
    void unbind() override;
    void draw(int index_count) override;

};

class GLFrameBuffer : public FrameBuffer {

public:
    void createBuffers(GLuint width, GLuint height) override;
    void deleteBuffers() override;
    void bind() override;
    void unbind() override;
    uint32_t getTexture() override;
};

#endif //FINITY_GUI_GLBUFFERMANAGER_H
