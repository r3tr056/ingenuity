#pragma once

#ifndef FINITY_GL_RENDERER_SHADERPROGRAM_H
#define FINITY_GL_RENDERER_SHADERPROGRAM_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/include/glad/gl.h>
#include <unordered_map>
#include <string>

class GLShaderProgram {

private:
	void getUniforms();

	std::unordered_map<std::string, int> mUniforms;

	GLuint mProgramID{ 0 };
	std::string mProgramName;

public:
	GLShaderProgram(const std::string& programName, const GLuint programID);
	~GLShaderProgram();

	GLShaderProgram(GLShaderProgram&& other) {
		mUniforms = other.mUniforms;
		mProgramID = other.mProgramID;
		mProgramName = other.mProgramName;

		other.mUniforms.clear();
		other.mProgramID = 0;
		other.mProgramName.clear();
	}

	GLShaderProgram& operator=(GLShaderProgram other) noexcept(true) {
		std::swap(mUniforms, other.mUniforms);
		std::swap(mProgramID, other.mProgramID);
		std::swap(mProgramName, other.mProgramName);
		return *this;
	}

	GLShaderProgram(const GLShaderProgram&) = delete;
	GLShaderProgram& operator=(const GLShaderProgram&) = delete;

	void Bind() const;
	void DeleteProgram() const;

	GLShaderProgram& SetUniformi(const std::string& uniformName, const int value);
	GLShaderProgram& SetUniformf(const std::string& uniformName, const float value);
	GLShaderProgram& SetUniform(const std::string& uniformName, const glm::ivec2& value);
	GLShaderProgram& SetUniform(const std::string& uniformName, const glm::vec2& value);
	GLShaderProgram& SetUniform(const std::string& uniformName, const glm::vec3& value);
	GLShaderProgram& SetUniform(const std::string& uniformName, const glm::vec4& value);
	GLShaderProgram& SetUniform(const std::string& uniformName, const glm::mat3x3& value);
	GLShaderProgram& SetUniform(const std::string& uniformName, const glm::mat4x4& value);

	auto GetProgramName() const noexcept { return mProgramName; }
};

#endif