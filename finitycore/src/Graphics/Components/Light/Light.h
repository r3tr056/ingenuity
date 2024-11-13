#pragma once
#ifndef FINITY_GUI_LIGHT_H
#define FINITY_GUI_LIGHT_H

#include "../glShader.h"

namespace finitycore::Core::Graphics::Components {

    class Light {
    public:
        void update(Shader* shader) {
            shader->setuniform("lightPosition", mPosition);
            shader->setuniform("lightColor", mColor);
        }

        Light() : mPosition(1.5f, 3.5f, 3.0f), mStrength(100.0f), mColor(1.0f, 1.0f, 1.0f, 1.0f) {}
        ~Light() = default;

    private:
        glm::vec3 mPosition;
        glm::vec4 mColor;
        GLfloat mStrength;
    };

    struct StaticPointLight {
        StaticPointLight(const glm::vec3& color, const glm::vec3& position) : mColor(color), mPosition(position) { }

        glm::vec3 mColor;
        glm::vec3 mPosition;
    };

    struct StaticSpotLight {
        StaticSpotLight(const glm::vec3& color, const glm::vec3& position, const glm::vec3& direction, const GLfloat cutoff, const GLfloat outerCutoff) : mColor(color), mPosition(position), mDirection(direction), mCutoff(cutoff), mOuterCutoff(outerCutoff) {}

        glm::vec3 mColor;
        glm::vec3 mPosition;
        glm::vec3 mDirection;
        GLfloat mCutoff;
        GLfloat mOuterCutoff;
    };

    struct StaticDirectionalLight {
        StaticDirectionalLight() = default;
        StaticDirectionalLight(const glm::vec3& color, const glm::vec3& direction) : mColor(color) {}

        glm::vec3  mColor;
        glm::vec3 mDirection;
    };

}

#endif //FINITY_GUI_LIGHT_H
