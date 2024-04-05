#pragma once

#include <GLFW/glfw3.h>

enum class EInputButton {
	LEFT = 0,
	RIGHT = 1,
	MIDDLE = 2,
	NONE = 9,
};

class Input {
public:
	static EInputButton GetPressedButton(GLFWwindow* window) {
		if (glfwGetMouseButton(window, 0) == GLFW_PRESS) {
			return EInputButton::LEFT;
		}
		else if (glfwGetMouseButton(window, 1) == GLFW_PRESS) {
			return EInputButton::RIGHT;
		}
		else if (glfwGetMouseButton(window, 2) == GLFW_PRESS) {
			return EInputButton::MIDDLE;
		}
		return EInputButton::NONE;
	}
};