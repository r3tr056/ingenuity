
#include "glShader.h"


void Shader::init(const std::string& vertexShaderFile, const std::string& fragShaderFile) {
    
    std::ifstream is_vs(vertexShaderFile);
    const std::string f_vs((std::istreambuf_iterator<char>(is_vs)), std::istreambuf_iterator<char>());
    std::ifstream is_fs(fragShaderFile);
    const std::string f_fs((std::istreambuf_iterator<char>(is_fs)), std::istreambuf_iterator<char>());

    program_id_ = glCreateProgram();

    GLuint vs = compile(GL_VERTEX_SHADER, f_vs);
    GLuint fs = compile(GL_FRAGMENT_SHADER, f_fs);
    link(vs, fs);
}

GLuint Shader::compile(GLuint shaderType,const std::string &shaderSrc) {
    GLuint id_ = glCreateShader(shaderType);
    const char* c_source = shaderSrc.c_str();
    glShaderSource(id_, 1, &c_source, nullptr);
    glCompileShader(id_);

    checkCompileErr(id_);
    return id_;
}

void Shader::link(const GLuint vs, const GLuint fs) {
    glAttachShader(program_id_, vs);
    glAttachShader(program_id_, fs);
    glLinkProgram(program_id_);
    checkLinkingErr(program_id_);
    glDeleteShader(vs);
    glDeleteShader(fs);
}


void Shader::use() const {
    glUseProgram(program_id_);
}

void Shader::unload() const {
    glDeleteProgram(program_id_);
}
template<>
void Shader::setuniform(const std::string &name, GLint val) {
    glUniform1i(glGetUniformLocation(program_id_, name.c_str()), val);
}

template<>
void Shader::setuniform(const std::string &name, const glm::vec3& val) {
    glProgramUniform3fv(program_id_, glGetUniformLocation(program_id_, name.c_str()), 1, glm::value_ptr(val));
}

template<>
void Shader::setuniform(const std::string &name, const glm::vec4& val) {
    glProgramUniform4fv(program_id_, glGetUniformLocation(program_id_, name.c_str()),1, glm::value_ptr(val));
}
template<>
void Shader::setuniform(const std::string &name, GLboolean val) {
    glUniform1i(glGetUniformLocation(program_id_, name.c_str()), val);
}

template<>
void Shader::setuniform(const std::string &name, const glm::mat4& val) {
    glUniformMatrix4fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

template<>
void Shader::setuniform(const std::string &name, GLfloat val) {
    glUniform1f(glGetUniformLocation(program_id_, name.c_str()), val);
}

template<>
void Shader::setuniform(const std::string &name, GLfloat val1, GLfloat val2) {
    glUniform2f(glGetUniformLocation(program_id_, name.c_str()), val1, val2);
}

template<>
void Shader::setuniform(const std::string &name, GLfloat val1, GLfloat val2, GLfloat val3) {
    glUniform3f(glGetUniformLocation(program_id_, name.c_str()), val1, val2, val3);
}

template<>
void Shader::setuniform<float*>(const std::string &name, GLfloat* val) {
    glUniformMatrix4fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, val);
}

void Shader::checkCompileErr(GLuint shader_id) const {
    GLint success;
    auto* infoLog = new GLchar[1024];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, 1024, nullptr, infoLog);
        fprintf(stderr, "Error compiling Vertex Shader: %s \n", infoLog);
    }
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(program_id_, 1024, nullptr, infoLog);
        fprintf(stderr, "Error compiling Fragment Shader: %s \n", infoLog);
    }
    delete[] infoLog;
}

void Shader::checkLinkingErr(GLuint shader_id) const {
    GLint success;
    auto *infoLog = new GLchar[1024];
    glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_id, 1024, nullptr, infoLog);
        std::cout << "Error Linking Shader Program:\n" << infoLog << std::endl;
    }
    delete[] infoLog;
}
