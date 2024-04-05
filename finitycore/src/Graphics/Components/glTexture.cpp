
#include "glTexture.h"

void GLTexture::activateTexture(const int texIndex) {
    int textureIndex = 33984 + texIndex;
    glActiveTexture(textureIndex);
}

void GLTexture::Bind2d() const {
    glBindTexture(GL_TEXTURE_2D, mTexture);
}