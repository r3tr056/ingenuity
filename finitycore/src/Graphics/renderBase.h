#include "graphics/components/Camera/Camera.h"
#include "graphics/components/VertexHolder.h"
#include "gfx/Window.h"

class VertexIndexBuffer {
protected:
	GLuint mVBO;
	GLuint mVAO;
	GLuint mIBO;

public:
	VertexIndexBuffer() : mVBO{ 0 }, mVAO{ 0 }, mIBO{ 0 } {}

	// Pure virtual functions
	virtual void createBuffers(const std::vector<VertexHolder>& vertices, const std::vector<GLuint>& indices) = 0;
	virtual void deleteBuffers() = 0;
	virtual void bind() = 0;
	virtual void unbind() = 0;
	virtual void draw(int index_count) = 0;
};

class FrameBuffer {
protected:
	GLuint mFBO = 0;
	GLuint mTexId = 0;
	GLuint mDepthId = 0;
	GLuint mWidth = 0;
	GLuint mHeight = 0;

public:
	FrameBuffer() : mFBO{ 0 }, mDepthId{ 0 } {}

	// Pure virtual functions
	virtual void createBuffers(GLuint width, GLuint height) = 0;
	virtual void deleteBuffers() = 0;
	virtual void bind() = 0;
	virtual void unbind() = 0;
	virtual GLuint getTexture() = 0;
};

class RenderContext {
protected:
    finWindow* mWindow = 0;

public:
	RenderContext() : mWindow(nullptr) {}

	virtual bool init(finWindow* window) {
		mWindow = window;
		return true;
	}
	virtual void preRender() = 0;
	virtual void postRender() = 0;
	virtual void end() = 0;
};