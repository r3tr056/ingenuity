#pragma once
#ifndef FINITY_GUI_MESH_H
#define FINITY_GUI_MESH_H
#include <GL/glew.h>

#include <string>
#include <vector>
#include "VertexHolder.h"

#include <memory>
#include "GLShader.h"
#include "graphics/glBufferManager.h"

class Mesh {
public:
    std::vector<VertexHolder> mVertices;
    std::vector<GLuint> mVertexIndices;
    glm::vec4 mColor = { 1.0f, .0f, .0f, 1.0f };
    GLfloat mRoughness = .2f;
    GLfloat mMetallic = .1f;
    std::unique_ptr<GLVertexIndexBuffer> mRenderBufferMgr;

public:
    Mesh() = default;
    ~Mesh();
    bool load(const std::string & filePath);
    void addVertex(const VertexHolder & vertex) { mVertices.push_back(vertex); }
    void addVertexIndex(GLuint vertex_idx) { mVertexIndices.push_back(vertex_idx); }
    std::vector<GLuint> getVertexIndices() { return mVertexIndices; }
    void update(Shader* shader);
    void init();
    void createBuffers();
    void deleteBuffers();
    void render();
    void bind();
    void unbind();

};

#endif //FINITY_GUI_MESH_H
