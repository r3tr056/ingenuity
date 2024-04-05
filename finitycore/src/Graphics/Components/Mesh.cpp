
#include "Mesh.h"
#include "../../modules/importers/meshImporter.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <string>

void Mesh::update(Shader *shader) {
    // PBR Color
    shader->setuniform("albedo", mColor);
    shader->setuniform("roughness", mRoughness);
    shader->setuniform("metallic", mMetallic);
    shader->setuniform("ao", 1.0f);
}

void Mesh::init() {
    mRenderBufferMgr = std::make_unique<GLVertexIndexBuffer>();
    createBuffers();
}

// Destructor
Mesh::~Mesh() {
    deleteBuffers();
}

bool Mesh::load(const std::string &filePath) {
    MeshImporter::MeshImportFlags cMeshImportFlag;
    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(filePath.c_str(), cMeshImportFlag);

    if (pScene && pScene->HasMeshes()) {
        // Reset the scene vertices and vertex indices
        mVertexIndices.clear();
        mVertices.clear();

        auto* mesh = pScene->mMeshes[0];
        for (GLuint i=0; i<mesh->mNumVertices; i++) {
            VertexHolder vh{};
            vh.mPos = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            vh.mNormal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
            addVertex(vh);
        }

        for (GLsizei i=0; i<mesh->mNumFaces; i++) {
            aiFace *face = mesh->mFaces;
            for (GLsizei j=0; j<face->mNumIndices; j++)
                addVertexIndex(face->mIndices[j]);
        }
        init();
        return true;
    }
    return false;
}

void Mesh::createBuffers() {
    mRenderBufferMgr->createBuffers(mVertices, mVertexIndices);
}

void Mesh::deleteBuffers() {
    mRenderBufferMgr->deleteBuffers();
}

void Mesh::bind() {
    mRenderBufferMgr->bind();
}

void Mesh::unbind() {
    mRenderBufferMgr->unbind();
}

void Mesh::render() {
    mRenderBufferMgr->draw((GLint)mVertexIndices.size());
}
