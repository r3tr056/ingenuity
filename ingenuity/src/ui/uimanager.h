# pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <imgui.h>
// OpenGL 3 and GLFW
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

class UIManager {
	UIManager(GLFWwindow* glfwWindow, Styling::Style style, const std::string glslVersion);
	~UIManager();

	void ApplyStyle(Styling::Style style);
	bool LoadFont(const std::string& id, const std::string& path, float font_Size);
	bool UnloadFont(const std::string& id);
	bool UseFont(const std::string& id);
	void UseDefaultFont();
	void EnableEditorLayoutSave(bool value);
	bool IsEditorLayoutSaveEnabled() const;
	void SetEditorLayoutSaveFilename(const std::string& filename);
	void SetEditorLayoutAutosaveFrequency(float freq);
	float GetEditorLayoutAutosaveFrequency(float freq);
	void EnableDocking(bool value);
	void Resetlayout(const std::string& config) const;
	bool IsDockingEnabled() const;
	void SetCanvas(Components::Canvas& canvas);
	void RemoveCanvas();
	void Render();
	void PushCurrentFloat();
	void PopCurrentFont();
};