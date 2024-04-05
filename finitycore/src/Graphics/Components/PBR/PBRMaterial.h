#pragma once
#ifndef FINITY_GUI_PBRMATERIAL_H
#define FINITY_GUI_PBRMATERIAL_H

#include <glm/vec3.hpp>
#include <memory>
#include <array>
#include <string>
#include <string_view>
#include <GL/glew.h>

class PBRMaterial {
private:
    std::array<GLuint, 5> mMaterialTextures;
    std::array<glm::vec3, 5> mMaterialColors;
    GLfloat mAlpha;
    GLuint mAlphaMaskTexture;

public:
    std::string name;

    PBRMaterial();

    enum ParameterType {
        ALBEDO = 0,
        AO,
        METALLIC,
        NORMAL,
        ROUGHNESS
    };

    virtual void init(const std::string name, const std::string albedoPath, const std::string aoPath, const std::string metallicPath, const std::string normalPath, const std::string roughnessPath);

    virtual void init(const std::string name, const glm::vec3& albedo, const glm::vec3& ao, const glm::vec3& metallic, const glm::vec3& normal, const glm::vec3& roughness, const GLfloat alpha = 1.0f);

    auto operator==(const PBRMaterial& rhs) const noexcept {
        return name == rhs.name;
    }

    auto getAlphaValue() const noexcept {
        return mAlpha;
    }

    auto getAlphaMask() const noexcept {
        return mAlphaMaskTexture;
    }

};

#endif //FINITY_GUI_PBRMATERIAL_H
