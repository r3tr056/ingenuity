#include "Window.h"
#include "input.h"

bool finWindow::init(GLsizei width, GLsizei height, const char *title, const GLint swapInterval=1) {
	m_size = { width, height };
    mRenderCtx->init(this);
    mUICtx->init(this);
    // The panels
    mSceneView = std::make_unique<SceneView>();
    mPropertyPanel = std::make_unique<PropertyPanel>();
    mPropertyPanel->setMeshLoadCallback(
        [this](std::string filePath) { mSceneView->loadMesh(filePath); }
    );
    // Create a window on the primary monitor
    m_glfwWindow = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), nullptr);
    if (m_glfwWindow == nullptr)
        fprintf(stderr, "ERROR : Failed to create GLFW Window");
    glfwMakeContextCurrent(m_glfwWindow);
    glfwSwapInterval(swapInterval);
    return mIsRunning;
}

void finWindow::render() {
    // Divide into phases
    mRenderCtx->preRender();
    mUICtx->preRender();
    mSceneView->render();
    mPropertyPanel->drawPanel(mSceneView.get());
    mUICtx->postRender();
    mRenderCtx->postRender();
    handleInput();
}

finWindow::~finWindow() {
    glfwDestroyWindow(m_glfwWindow);
    mUICtx->end();
    mRenderCtx->end();
}

void finWindow::onResize(int width, int height) {
	m_size = { width, height };
    mSceneView->resize(m_size.first, m_size.second);
    render();
}

void finWindow::onScroll(double dT) {
    mSceneView->onMouseWheel(dT);
}

void finWindow::onKeyPress(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {

    }
}

void finWindow::onClose() {
    mIsRunning = false;
}

void finWindow::handleInput() {
    if (glfwGetKey(m_glfwWindow, GLFW_KEY_W) == GLFW_PRESS) {
        mSceneView->onMouseWheel(-0.4f);
    }
    if (glfwGetKey(m_glfwWindow, GLFW_KEY_S) == GLFW_PRESS) {
        mSceneView->onMouseWheel(0.4f);
    }
    if (glfwGetKey(m_glfwWindow, GLFW_KEY_F) == GLFW_PRESS) {
        mSceneView->resetView();
    }
    double x, y;
    glfwGetCursorPos(m_glfwWindow, &x, &y);
    mSceneView->onMouseMove(x, y, Input::GetPressedButton(m_glfwWindow));
}