#pragma once
#ifndef FINITY_GUI_GLTEXTURE_H
#define FINITY_GUI_GLTEXTURE_H

#include <GL/glew.h>
#include <string>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif

#ifndef GLFW_MAX_TEXTURES
#define GLFW_MAX_TEXTURES 256
#endif

class GLTexture {
private:
    GLfloat mTexCoords;
    GLuint mTexture;
    // TODO : setup helper functions for mfullPath
    std::string mSamplerName, mTexturePath, mfullPath;
    GLuint tex_ids[GLFW_MAX_TEXTURES];

public:
    enum WrapMode {
        REPEAT = GL_REPEAT,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
        EDGE_CLAMP = GL_CLAMP_TO_EDGE,
        BORDER_CLAMP = GL_CLAMP_TO_BORDER
    };

    enum TexFiltering {
        // Tex Sampling using nearest neighbour Interpolation or linear interpolating
        // and nearest mipmap or using linear interpolation to match pixel size
        FILTER_NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
        FILTER_LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
        FILTER_NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
        FILTER_LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
    };

    GLTexture(const std::string& modelPath, std::string& texturePath, const std::string& samplerName,
        const GLfloat borderColor[], const WrapMode wrapMode = WrapMode::REPEAT, const TexFiltering texFilteringMode = TexFiltering::FILTER_LINEAR_MIPMAP_LINEAR) : mSamplerName(samplerName), mTexturePath(texturePath) {

        mfullPath = modelPath;
        mfullPath += std::string(texturePath);

        glGenTextures(1, &mTexture);
        glBindTexture(GL_TEXTURE_2D, mTexture);

        // Set the texture params for wrap mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

        // GLTexture filtering
        // By default Linearly interpolate b/w the two closest mipmaps and samples the texture via
        // linear interpolation
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texFilteringMode);
        // Mipmaps don't apply to magnification
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (GLEW_EXT_texture_filter_anisotropic) {
            // Anisotropic filtering
            GLfloat aniso = .0f;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLint)(aniso / 2.0f));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, .0f);
        }

        // TODO : Implement a resource manager that uses stbi_load internally and returns
        // width, height, nrChannels, and textureData
        GLint width = 100, height = 100, nrChannels = 10;
        finTextureData* texData = new finTextureData(texturePath, width, height, nrChannels);
        if (!texData->mtexData)
            fprintf(stderr, "ERROR : Failed to load texture data\n");

        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, texData->mwidth, texData->mheight, 0, GL_RGB, GL_UNSIGNED_BYTE, texData->mtexData);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Free the data
        stbi_image_free(texData->mtexData);
    }

    bool operator==(const GLTexture& rhs) const { return mfullPath == rhs.getFullPath(); }

    GLuint getTexture() const noexcept { return mTexture; }
    std::string getFullPath() const noexcept { return mfullPath; }
    std::string getRelativePath() const noexcept { return mTexturePath; }
    std::string getSampler() const noexcept { return mSamplerName; }
    void Bind2d() const;
    void activateTexture(int texIndex);
};

class finTextureData {
public:
    GLint mwidth, mheight;
    GLint m_nrChannels;
    unsigned char *mtexData;

public:
    finTextureData(std::string& texturePath, const GLint width, const GLint height, const GLint nrChannels) : mwidth(width), mheight(height), m_nrChannels(nrChannels) {
        mtexData = stbi_load(texturePath.c_str(), &mwidth, &mheight, &m_nrChannels, 0);
    }
};

#endif //FINITY_GUI_GLTEXTURE_H


