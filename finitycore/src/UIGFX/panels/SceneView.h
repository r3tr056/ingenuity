#pragma once
#ifndef FINITY_GUI_SCENEVIEW_H
#define FINITY_GUI_SCENEVIEW_H

#include <memory>
#include "graphics/components/Camera/Camera.h"
#include "graphics/components/Light.h"
#include "graphics/components/glShader.h"
#include "graphics/components/Mesh.h"
#include "graphics/glBufferManager.h"
#include <utility>
#include <glm/vec3.hpp>

// The application render viewport
class SceneView {

private:
    std::unique_ptr<Camera> mCamera;
    std::unique_ptr<GLFrameBuffer> mFrameBuffer;
    std::unique_ptr<Shader> mShader;
    std::unique_ptr<Light> mLight;
    std::shared_ptr<Mesh> mMesh;
    glm::vec2 mSize;

public:
    SceneView(): mCamera(nullptr), mFrameBuffer(nullptr), mShader(nullptr), mLight(nullptr), mSize(800, 600) {
        mFrameBuffer = std::make_unique<GLFrameBuffer>();
        mFrameBuffer->createBuffers(800, 600);
        mShader = std::make_unique<Shader>();
        mShader->init("shaders/vs.shader", "shaders/fs_pbr.shader");
        mLight = std::make_unique<Light>();
        mCamera = std::make_unique<Camera>(glm::vec3(0, 0, 3), 45.0f, 1.3f, 0.1f, 100.0f);
    }

    ~SceneView() { mShader->unload(); }

    Light* getLight() { return mLight.get(); }
    void resize(GLsizei width, GLsizei height);
    void onMouseMove(GLfloat x, GLfloat y, EInputButton btn);
    void render();
    void loadMesh(std::string &filepath);
    void setMesh(std::shared_ptr<Mesh> mesh) { mMesh = std::move(mesh); }
    std::shared_ptr<Mesh> getMesh() { return mMesh; }
    void onMouseWheel(GLdouble dT);
    void resetView() { mCamera->reset(); }

};

#endif //FINITY_GUI_SCENEVIEW_H
