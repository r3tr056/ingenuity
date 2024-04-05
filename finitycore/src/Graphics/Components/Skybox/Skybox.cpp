// THE SKYBOX ISNT READY YET

#include "Skybox.h"
#include "../GLShader.h"
#include <array>
#include <glm/gtc/matrix_transform.hpp>

void finSkybox::init(const std::string hdrPath, const std::size_t res) {
    std::array<glm::vec3, 4> screenQuadVertices;

    mquadVAO.init();
    mquadVAO.bind();
}