#include <GL/glew.h>

#include "glContext.h"
#include <GLFW/glfw3.h>


static void onKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	auto pWindow = static_cast<finWindow*>(glfwGetWindowUserPointer(window));
	pWindow->onKeyCallback(key, scanCode, action, mods);
}

static void onScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	auto pWindow = static_cast<finWindow*>(glfwGetWindowUserPointer(window));
	pWindow->onScroll(yoffset);
}

static void onWindowSizeCallback(GLFWwindow* window, int width, int height) {
	auto pWindow = static_cast<finWindow*>(glfwGetWindowUserPointer(window));
	pWindow->onResize(width, height);
}

static void onWindowCloseCallback(GLFWwindow* window) {
	auto pWindow = static_cast<finWindow*>(glfwGetWindowUserPointer(window));
	pWindow->onClose();
}

bool OpenGLContext::init(finWindow* window) {
	__super::init(window);

	// Init the lib
	if (!glfwInit()) {
		fprintf(stderr, "Error: GLFW Window could'nt be initialised\n");
		return false;
	}

	// Create the window and store this window as window pointer
	// to be used in callback functions
	auto glWindow = glfwCreateWindow(window->m_size.second, window->m_size.first, window->m_title.c_str(), nullptr, nullptr);
	window->setNativeWindow(glWindow);

	if (!glWindow) {
		fprintf(stderr, "Error : GLFW window can't be created\n");
		return false;
	}

	glfwSetWindowUserPointer(glWindow, window);
	glfwSetKeyCallback(glWindow, onKeyCallback);
	glfwSetScrollCallback(glWindow, onScrollCallback);
	glfwSetWindowSizeCallback(glWindow, onWindowSizeCallback);
	glfwSetWindowCloseCallback(glWindow, onWindowCloseCallback);
	glfwMakeContextCurrent(glWindow);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error : %s\n", glewGetErrorString(err));
		return false;
	}
	glEnable(GL_DEPTH_TEST);
	return true;
}

void OpenGLContext::preRender() {
	glViewport(0, 0, mWindow->m_size.first, mWindow->m_size.second);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::postRender() {
	glfwPollEvents();
	glfwSwapBuffers((GLFWwindow*)mWindow->getNativeWindow());
}

void OpenGLContext::end() {
	glfwDestroyWindow((GLFWwindow*)mWindow->getNativeWindow());
	glfwTerminate();
}