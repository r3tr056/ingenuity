#include "application.h"

Application::Application(const std::string& appName) {
	// The application main window
	mWindow = std::make_unique<finWindow>();
	mWindow->init(1024, 720, appName.c_str(), 1);
}

void Application::loop() {
	while (mWindow->isRunning()) {
		// Put all the render methods in Window->render()
		mWindow->render();
	}
}

void Application::IsRunning() {

}