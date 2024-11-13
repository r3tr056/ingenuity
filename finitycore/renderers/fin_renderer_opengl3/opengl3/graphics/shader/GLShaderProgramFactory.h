#pragma once

#ifndef FINITY_GL_RENDERER_SHADERPORGRAMFACTORY_H
#define FINITY_GL_RENDERER_SHADERPORGRAMFACTORY_H


#include "GLShaderProgram.h"
#include "ShaderStage.h"

#include <optional>
#include <vector>

class GLShaderProgramFactory {
public:
	static std::optional<GLShaderProgram> createShaderProgram(
		const std::string& programName,
		const std::vector<ShaderStage>& stages
	);
};

#endif