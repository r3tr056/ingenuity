
#include "SceneView.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"

void SceneView::resize(GLsizei width, GLsizei height) {
    mSize.x = width;
    mSize.y = height;
    mFrameBuffer->createBuffers((int32_t)mSize.x, (int32_t)mSize.y);
}
void SceneView::onMouseMove(GLfloat x, GLfloat y, EInputButton btn) {
    mCamera->onMouseMove(x, y, btn);
}

void SceneView::onMouseWheel(GLdouble dT) {
    mCamera->onMouseWheel(dT);
}

void SceneView::loadMesh(std::string &filepath) {
    if (!mMesh)
        mMesh = std::make_shared<Mesh>();
    mMesh->load(filepath);
}

void SceneView::render() {
    mShader->use();
    mLight->update(mShader.get());
    mFrameBuffer->bind();

    if (mMesh) {
        mMesh->update(mShader.get());
        mMesh->render();
    }
    mFrameBuffer->unbind();
    ImGui::Begin("Scene");

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    mSize = { viewportPanelSize.x, viewportPanelSize.y };
    mCamera->setAspect(mSize.x / mSize.y);
    mCamera->update(mShader.get());

    // add rendered texture to ImGui scene window
    uint64_t textureID = mFrameBuffer->getTexture();
    ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ mSize.x, mSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

    ImGui::End();
}