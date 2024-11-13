
#include "GLShaderProgram.h"

#include <cassert>
#include <iostream>

GLShaderProgram::GLShaderProgram(const std::string& programName, const GLuint programID) {
	getUniforms();
}

GLShaderProgram::~GLShaderProgram() {
	DeleteProgram();
}

void GLShaderProgram::Bind() const {
	assert(mProgramID != 0);
	glUseProgram(mProgramID);
}

void GLShaderProgram::DeleteProgram() const {
	if (mProgramID != 0) {
		std::cout << "Deleting program: " << mProgramName << '\n';
		glDeleteProgram(mProgramID);
	}
}

GLShaderProgram& GLShaderProgram::SetUniformi(const std::string& uniformName, const int value) {
	glUniform1i(mUniforms.at(uniformName), value);
	return *this;
}

GLShaderProgram& GLShaderProgram::SetUniformf(const std::string& uniformName, const float value) {
	glUniform1f(mUniforms.at(uniformName), value);

	return *this;
}

GLShaderProgram& GLShaderProgram::SetUniform(const std::string& uniformName, const glm::ivec2& value) {
	glUniform2iv(mUniforms.at(uniformName), 1, &value[0]);

	return *this;
}

GLShaderProgram& GLShaderProgram::SetUniform(const std::string& uniformName, const glm::vec2& value) {
	glUniform2f(mUniforms.at(uniformName), value.x, value.y);

	return *this;
}

GLShaderProgram& GLShaderProgram::SetUniform(const std::string& uniformName, const glm::vec3& value) {
	glUniform3f(mUniforms.at(uniformName), value.x, value.y, value.z);

	return *this;
}

GLShaderProgram& GLShaderProgram::SetUniform(const std::string& uniformName, const glm::vec4& value) {
	glUniform4f(mUniforms.at(uniformName), value.x, value.y, value.z, value.w);

	return *this;
}

GLShaderProgram& GLShaderProgram::SetUniform(const std::string& uniformName, const glm::mat3x3& value) {
	glUniformMatrix3fv(mUniforms.at(uniformName), 1, GL_FALSE, value_ptr(value));

	return *this;
}

GLShaderProgram& GLShaderProgram::SetUniform(const std::string& uniformName, const glm::mat4x4& value) {
	glUniformMatrix4fv(mUniforms.at(uniformName), 1, GL_FALSE, value_ptr(value));

	return *this;
}

void GLShaderProgram::getUniforms() {

	int total = -1;
	glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORMS, &total);
	for (auto i = 0; i < total; ++i) {
		auto name_len = -1, num = -1;
		GLenum type = GL_ZERO;
		char name[100];
		glGetActiveUniform(mProgramID, static_cast<GLuint>(i), sizeof(name) - 1, &name_len, &num, &type, name);
		name[name_len] = 0;

		const auto nameStr = std::string(name);

		// TODO: Filter out uniform block members using glGetActiveUniformsiv
		mUniforms.try_emplace(nameStr, glGetUniformLocation(mProgramID, name));
	}
}