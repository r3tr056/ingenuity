/*	NOTICE : Precompiled Header support for this project has been turned off
	this has been done to later develop seperate PCH files for the graphics
	and the UI modules
*/

#pragma once

// Std includes
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


// GL includes
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#define log_info(message) \
	do {\
		std::cout << "[INFO] " << message << std::endl; \
	} while (false)


#define log_error(message) \
	do {\
		std::cout << "[ERROR] " << message << std::endl; \
	} while (false)

#define BIND_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }