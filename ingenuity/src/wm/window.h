#pragma once

#include <string>
#include <unordered_map>

#include <GLFW/glfw3.h>

namespace ingenuity {
	namespace wm {

		class Window {
		public:
			Window(const Context::Device& device, const Settings::WindowSettings& pWindowSettings);
			~Window();

			void SetIcon(const std::string& filePath);
			void SetIconFromMemory(uint8_t* data, uint32_t width, uint32_t height);
			
			static Window* FindInstance(GLFWwindow* glfwWindow);

			void SetSize(uint16_t width, uint16_t height);
			void SetMinimumSize(uint16_t minWidth, int16_t minHeight);
			void SetMaxSize(int16_t maxWidth, int16_t maxHeight);
			void SetPosition(int16_t x, int16_t y);
			void Minimize() const;
			void Maximize() const;
			void Restore() const;
			void Hide() const;
			void Show() const;
			void Focus() const;
			void SetShouldClose(bool value) const;
			bool ShouldClose() const;
			void SetFullscreen(bool value);
			void ToggleFullscreen();
			bool IsFullscreen() const;
			bool IsHidden() const;
			bool IsVisible() const;
			bool IsMaximised() const;
			bool IsMinimized() const;
			bool IsFoucused() const;
			bool IsResizable() const;
			bool IsDecorated() const;
			bool MakeCurrentContext() const;
			void SwapBuffers() const;
			void SetCursorMode(Cursor::CursorMode cursorMode);
			void SetCursorShape(Cursor::CursorShape curShape);
			void SetCursorPosition(int16_t x, int16_t y);
			void SetTitle(const std::string& title);
			void SetRefreshRate(int32_t refRate);
			
			std::string GetTitle() const;
			std::pair<uint16_t, uint16_t> GetSize() const;
			std::pair<int16_t, int16_t> GetMinimumSize() const;
			std::pair<int16_t, int16_t> GetPosition() const;
			std::pair<uint16_t, uint16_t> GetFramebufferSize() const;
			Cursor::CursorMode GetCursorMode() const;
			Cursor::CursorShape GetCursorShape() const;
			int32_t GetRefreshRate() const;
			GLFWwindow* GetGLFWWindow() const;

		private:
			void CreateGLFWWindow(const Settings::WindowSettings& windowSettings);

			// callback bindings
			void BindKeyCallback() const;
			void BindMouseCallback() const;
			void BindResizeCallback() const;
			void BindFramebufferResizeCallback() const;
			void BindCursorMoveCallback() const;
			void BindMoveCallback() const;
			void BindIconifyCallback() const;
			void BindFocusCallback() const;
			void BindCloseCallback() const;

			// Internal Event Listeners
			void OnResize(uint16_t width, uint16_t height);
			void OnMove(int16_t x, int16_t y);

			// Internal helpers
			void UpdateSizeLimit() const;

		private:
			static std::unordered_map<GLFWwindow*, Window*> __WINDOWS_MAP;
			const Context::Device& mDevice;
			GLFWwindow* m_glfwWindow;

			std::string m_title;
			std::pair<uint16_t, uint16_t> m_size;
			std::pair<int16_t, int16_t> m_minSize;
			std::pair<int16_t, int16_t> m_maxSize;
			std::pair<int16_t, int16_t> m_pos;
			bool m_fullscreen;
			int32_t m_refRate;
			Cursor::CursorShape m_curShape;
			Cursor::CursorMode m_curMode;
		};
} }