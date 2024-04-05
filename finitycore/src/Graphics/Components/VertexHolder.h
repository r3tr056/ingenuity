#pragma once

#ifndef FINITY_GUI_VERTEXHOLDER_H
#define FINITY_GUI_VERTEXHOLDER_H

#include <string>
#include <glm/glm.hpp>

class VertexHolder {
public:
    VertexHolder() = default;
    VertexHolder(const std::vector<std::string> tokens);
    VertexHolder(const glm::vec3 &pos, const glm::vec3 &normal) : mPos(pos), mNormal(normal) {};
    ~VertexHolder() = default;

    glm::vec3 mPos;
    glm::vec3 mNormal;
};

#endif //FINITY_GUI_VERTEXHOLDER_H
