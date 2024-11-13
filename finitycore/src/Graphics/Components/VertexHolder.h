#pragma once

#ifndef FINITY_GUI_VERTEXHOLDER_H
#define FINITY_GUI_VERTEXHOLDER_H

#include <string>
#include <glm/glm.hpp>

class VertexHolder {
public:
    VertexHolder() = default;

    VertexHolder(const std::vector<std::string> tokens);

    VertexHolder(const glm::vec3& pos, const glm::vec2& texCoords) : mPos(pos), mTexCoords(texCoords) {};

    VertexHolder(const glm::vec3 &pos, const glm::vec3 &normal) : mPos(pos), mNormal(normal) {};

    VertexHolder(const glm::vec3& pos, const glm::vec2& texCoords, const glm::vec3& normal) : mPos(pos), mTexCoords(texCoords), mNormal(normal) {}

    VertexHolder(
        const glm::vec3& pos,
        const glm::vec2& texCoords,
        const glm::vec3& normal,
        const glm::vec3& tangent
    ) : mPos(pos), mTexCoords(texCoords), mNormal(normal), mTangent(tangent) {}

    ~VertexHolder() = default;

    glm::vec3 mPos;
    glm::vec3 mNormal;
    glm::vec3 mTangent;
    glm::vec2 mTexCoords;
};

#endif //FINITY_GUI_VERTEXHOLDER_H
