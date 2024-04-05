#pragma once

#include "UIGFX/Window.h"
#include <string>
#include <memory>

class Application {
public:
	Application(const std::string& appName);

	static Application& Instance() { return *sInstance; }

	void loop();
	void onStart();

	bool IsRunning() const;

private:
	static Application* sInstance;
	Context m_context;
	std::unique_ptr<finWindow> mWindow;
};