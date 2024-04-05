
#ifndef FINITY_GUI_GLSHADER_H
#define FINITY_GUI_GLSHADER_H

#include <GL/glew.h>

#include <string>
#include <vector>
#include <glm/detail/type_vec3.hpp>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    Shader() = default;
    void init(const std::string& vertexShaderFile, const std::string& fragShaderFile);
    void use() const;
    template<typename T> void setuniform(const std::string& name, T val);
    template<typename T> void setuniform(const std::string& name, T val1, T val2);
    template<typename T> void setuniform(const std::string& name, T val1, T val2, T val3);
    void unload() const;
    GLuint getProgramId() const { return program_id_; }

private:
    void checkCompileErr(GLuint shader_id) const;
    void checkLinkingErr(GLuint shader_id) const;
    GLuint compile(GLuint shaderType,const std::string &shaderSrc);
    void link(GLuint vs, GLuint fs);
    GLuint program_id_;

};

#endif //FINITY_GUI_GLSHADER_H
