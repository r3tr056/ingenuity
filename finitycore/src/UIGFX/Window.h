#pragma once
#ifndef FINITY_GUI_WINDOW_H
#define FINITY_GUI_WINDOW_H

#include "finPch.h"
#include "Panel.h"
#include "panels/PropertyPanel.h"
#include "panels/SceneView.h"
#include "graphics/glContext.h"
#include "graphics/uiContext.h"


const constexpr std::size_t MaxVertexBuffer { 512 * 1024 };
const constexpr std::size_t MaxElementBuffer { 128 * 1024 };

class finWindow {

public:
	static std::unordered_map<GLFWwindow*, finWindow*> __WINDOWS_MAP;

	GLFWwindow* m_glfwWindow;
    std::unique_ptr<UIContext> mUICtx;
    std::unique_ptr<OpenGLContext> mRenderCtx;
    std::unique_ptr<PropertyPanel> mPropertyPanel;
    std::unique_ptr<SceneView> mSceneView;
	std::vector<std::unique_ptr<finPanel>> m_abstractPanels;
    bool mIsRunning;
	std::pair<uint16_t, uint16_t> m_size;
	std::pair<int16_t, int16_t> m_minSize;
	std::pair<int16_t, int16_t> m_maxSize;
	std::pair<int16_t, int16_t> m_pos;
	int32_t m_refRate;
	bool m_fullscreen = false;
	const std::string m_title;
/*
	Cursor::CursorMode m_curMode;
	Cursor::CursorShape m_curShape;
*/

public:
    finWindow() : mIsRunning(true), m_glfwWindow(nullptr) {
        mUICtx = std::make_unique<UIContext>();
        mRenderCtx = std::make_unique<OpenGLContext>();
    }

    ~finWindow() = default;

    bool init(GLsizei width, GLsizei height,const char *title, const GLint swapInterval);
    void render();
    void handleInput();
    void *getNativeWindow() { return m_glfwWindow; }
    void setNativeWindow(void* window)
    {
        m_glfwWindow = (GLFWwindow*)window;
    }
    void onScroll(double dT);
    void onKeyPress(int key, int scancode, int action, int mods);
    void onResize(GLsizei width, GLsizei height);
    void onClose();
    bool isRunning() { return mIsRunning; }

	void SetIcon(const std::string& p_filePath);
	void SetIconFromMemory(uint8_t* p_data, uint32_t p_width, uint32_t p_height);

	static finWindow* FindInstance(GLFWwindow* glfwWindow);
	void SetSize(uint16_t width, uint16_t height);
	void SetMinSize(uint16_t width, uint16_t height);
	void SetMaxSize(uint16_t width, uint16_t height);
	void SetPos(uint16_t x, uint16_t y);
	void Minimize() const;
	void Maximize() const;
	void Restore() const;
	void Hide() const;
	void Show() const;
	void Focus() const;
	void SetShouldClose(bool value) const;
	bool ShouldClose() const;
	void SetFullScreen(bool value);
	void ToogleFullScreen();
	bool isFullScreen() const;
	bool isHidden() const;
	bool isVisible() const;
	bool isMaximised() const;
	bool isMinimized() const;
	bool isFocused() const;
	bool isResizable() const;
	bool isDecorated() const;
	bool MakeCurrentContext() const;
	void SwapBuffers() const;
	// void SetCursorMode(Cursor::CursorMode curMode);
	// void SetCursorShape(Cursor::CursorShape curShape);
	void SetCursorPos(int16_t x, int16_t y);
	void SetTitle(const std::string& title);
	void SetRefreshRate(int32_t refRate);

};

#endif //FINITY_GUI_WINDOW_H
