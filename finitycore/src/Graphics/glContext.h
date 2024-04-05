#pragma once

#include <GLFW/glfw3.h>
#include "renderBase.h"

class OpenGLContext: public RenderContext {
public:
	bool init(finWindow* window);
	void preRender() ;
	void postRender() ;
	void end() ;

};