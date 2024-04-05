#define GLFW_INCLUDE_
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <iostream>
#include "application.h"

int main(void) {
	auto finApp = std::make_unique<Application>("finity application");
	finApp->loop();

	return 0;
}