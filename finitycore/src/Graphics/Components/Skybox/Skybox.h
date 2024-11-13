#pragma once
#ifndef FINITY_GUI_SKYBOX_H
#define FINITY_GUI_SKYBOX_H

#include <string>

#include "../renderers/fin_renderer_opengl3/opengl3/graphics/buffers/GLVertexArray.h"

class Skybox {

public:
    void init(const std::string hdrPath, const std::size_t res=512);
    void draw();

    auto getIrradianceMap() const noexcept { return mIrradianceMap; }
    auto getPrefilterMap() const noexcept { return mPrefilterMap; }
    auto getBRGFLUT() const noexcept { return mbrdfLUT; }

private:
    unsigned int mIrradianceMap, mCubeVAO, mEnvCubeMap, mPrefilterMap, mbrdfLUT;
    void renderCache();

    GLVertexArray mquadVAO;
};

#endif //FINITY_GUI_SKYBOX_H
