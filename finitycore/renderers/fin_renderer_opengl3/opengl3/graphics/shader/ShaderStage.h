#pragma once

#ifndef FINITY_GL_RENDERER_SHADERSTAGE_H
#define FINITY_GL_RENDERER_SHADERSTAGE_H

#include <string>

struct ShaderStage {
	ShaderStage() noexcept = default;
	ShaderStage(const std::string& path, const std::string& type) : filePath{ path }, type{ type } {}

	std::string filePath;
	std::string type;
};

#endif