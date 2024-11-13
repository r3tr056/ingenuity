

#include "GLShaderProgramFactory.h"

#include <glad/include/glad/gl.h>

#include <iostream>
#include <unordered_map>

const std::unordered_map<std::string, int> Type2GL_ENUM{
	{ "vertex", GL_VERTEX_SHADER },
	{ "fragment", GL_FRAGMENT_SHADER },
	{ "geometry", GL_GEOMETRY_SHADER },
	{ "compute", GL_COMPUTE_SHADER }
};

void compile(const GLuint id, const GLchar* shaderCode) {
	glShaderSource(id, 1, &shaderCode, nullptr);
	glCompileShader(id);
}

bool compileStage(const GLuint id, const std::string& shaderCode) {
	GLint success{ GL_FALSE };
	GLint logLength{ -1 };

	compile(id, shaderCode.c_str());

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);

	std::vector<GLchar> infoLog(0, logLength);

	glGetShaderInfoLog(id, logLength, nullptr, infoLog.data());
	std::cout << fmt::format("{}", std::string(infoLog.cbegin(), infoLog.cend())) << std::endl;

	return success == GL_TRUE;
}

bool linkProgram(const GLuint id) {
	GLint success{ GL_FALSE };
	GLint logLength{ -1 };

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

	std::vector<GLchar> infoLog(0, logLength);
	glGetProgramInfoLog(id, logLength, nullptr, infoLog.data());
	std::cout << fmt::format("{}", std::string(infoLog.cbegin(), infoLog.cend())) << std::endl;

	return success == GL_TRUE;
}

bool validateProgram(const GLuint id) {
	GLint success{ GL_FALSE };
	GLint logLength{ -1 };

	glValidateProgram(id);
	glGetProgramiv(id, GL_VALIDATE_STATUS, &success);
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

	std::vector<GLchar> infoLog(0, logLength);
	glGetProgramInfoLog(id, logLength, nullptr, infoLog.data());
	std::cout << fmt::format("{}", std::string(infoLog.cbegin(), infoLog.cend())) << std::endl;

	return success == GL_TRUE;
}

void scanForIncludes(std::string& shaderCode) {
	std::size_t startPose = 0;
	const static std::string includeDirectives{ "#include " };

	// scan string for all lines with the include directives
	while ((startPose = shaderCode.find(includeDirectives, startPos)) != std::string::npos) {
		// Find pos of include directives
		const auto pos = startPos + includeDirectives.length() + 1;
		const auto length = shaderCode.find('"', pos);
		const auto pathToIncludeFile = shaderCode.substr(pos, length - pos);

		const auto includedFile = ResourceManager::GetInstance().LoadTextFile(pathToIncludeFile) + "\n";
		// insert into the shader code
		shaderCode.replace(startPos, (length + 1) - startPos, includedFile);

		startPos += includedFile.length();
	}
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	std::size_t start_pos = 0;

	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

std::optional<GLShaderProgram> GLShaderProgramFactory::createShaderProgram(
	const std::string& programName,
	const std::vector<ShaderStage>& stages
) {
	std::cout << "Building shader program " << programName << std::endl;

	std::vector<GLuint> shaderIds;

	bool success{ true };
	for (auto i = 0; i < stages.size(); ++i) {
		auto id{ glCreateShader(Type2GL_ENUM.at(stages[i].type)) };
		shaderIds.push_back(id);

		auto shaderCode{ ResourceManager::GetInstance().LoadTextFile(stages[i].filePath) };
		scanForIncludes(shaderCode);
		replaceAll(shaderCode, "hash ", "#");
		if (!compileStage(id, shaderCode)) {
			success = false;
			break;
		}
	}

	if (!success) {
		for (const auto id : shaderIds) {
			glDeleteShader(id);
		}
		return std::nullopt;
	}

	GLuint programID{ glCreateProgram() };

	for (const auto id : shaderIds) {
		glAttachShader(programID, id);
	}

	// link and validate shaders
	if (!linkProgram(programID) || !validateProgram(programID)) {
		for (const auto id : shaderIds) {
			glDetachShader(programID, id);
			glDeleteShader(id);
		}
		glDeleteProgram(programID);

		return std::nullopt;
	}

	for (const auto id : shaderIds) {
		glDetachShader(programID, id);
		glDeleteShader(id);
	}

	// leave uniform introspection to GLShaderProgram
	return std::make_optional<GLShaderProgram>({ programName, programID });
}