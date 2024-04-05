
#ifndef RENDERER_HARDWARECAPS_H
#define RENDERER_HARDWARECAPS_H

#include <GL/gl.h>
#include <GL/glew.h>

class Hardware {
private:
    struct HardwareCaps {
        float MaxAnisotropy;
        float MaxArrayTextureLayers;
        float MaxTextureColorSamples;
        float MaxTextureDepthSamples;
        float MaxVertexUniformBlocks;
        float MaxGeometryUniformBlocks;
        float MaxFragmentUniformBlocks;
        float MaxComputeWorkGroupSize;
        float MaxComputeWorkGroupCount;
    };
    
    HardwareCaps s_caps;

    
public:
// The Helper functions
    HardwareCaps queryHardwareCaps() {
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &s_caps.MaxAnisotropy);
        glGetFloatv(GL_MAX_ARRAY_TEXTURE_LAYERS_EXT, &s_caps.MaxArrayTextureLayers);
        glGetFloatv(GL_MAX_COLOR_TEXTURE_SAMPLES, &s_caps.MaxTextureColorSamples);
        glGetFloatv(GL_MAX_COMPUTE_WORK_GROUP_COUNT, &s_caps.MaxComputeWorkGroupCount);
        glGetFloatv(GL_MAX_COMPUTE_WORK_GROUP_SIZE, &s_caps.MaxComputeWorkGroupSize);
        glGetFloatv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &s_caps.MaxFragmentUniformBlocks);
        glGetFloatv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &s_caps.MaxGeometryUniformBlocks);
        glGetFloatv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &s_caps.MaxVertexUniformBlocks);
        glGetFloatv(GL_MAX_DEPTH_TEXTURE_SAMPLES, &s_caps.MaxTextureDepthSamples);

        return s_caps;
    }

};

#endif //RENDERER_HARDWARECAPS_H
