#pragma once
#ifndef FINITY_GUI_ENGINE_H
#define FINITY_GUI_ENGINE_H

#include <vector>
#include <string>
#include <memory>
#include <GLFW/glfw3.h>
#include <experimental/filesystem>
#include <unordered_map>

#include "../Timer.h"
#include "./components/Camera.h"

class finRenderEngine {
private:
    void terminate() const;

    std::vector<ModelPtr> cullViewFustrum() const;
    Timer mTimer;
    Camera mCamera;

    // Core System Referneces
    GLFWwindow *mWindow;
    RenderSystem *mRenderer;

    std::unordered_map<std::string, std::shared_ptr<SceneBase>> mSceneQueue;
    SceneBase* mActiveScene{ nullptr };

public:
    // NOTE : Not used now, we statically configure the engine inside the code
    // finRenderEngine(const std::experimental::filesystem::path& config);

    void addScene(const std::shared_ptr<SceneBase>& scene);
    void setActiveScene(const std::string sceneName);

    // Load the scene and run the update loop
    void execute();
};

#endif //FINITY_GUI_ENGINE_H
