
#include "Skybox.h"

#include "../renderers/fin_renderer_opengl3/opengl3/graphics/shader/GLShaderProgram.h"
#include "../renderers/fin_renderer_opengl3/opengl3/graphics/shader/GLShaderProgramFactory.h"
#include "../VertexHolder.h"

#include <array>
#include <glm/gtc/matrix_transform.hpp>

void Skybox::init(const std::string hdrPath, const std::size_t res) {
    const std::array<VertexHolder, 4> screenQuadVertices{
        VertexHolder({ -1.0f, 1.0f, 0.0f },{ 0.0f, 1.0f }),
        VertexHolder({ -1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f }),
        VertexHolder({ 1.0f, 1.0f, 0.0f },{ 1.0f, 1.0f }),
        VertexHolder({ 1.0f, -1.0f, 0.0f },{ 1.0f, 0.0f })
    };

    mquadVAO.init();
    mquadVAO.bind();
    mquadVAO.attachBuffer(GLVertexArray::BufferType::ARRAY, sizeof(VertexHolder) * screenQuadVertices.size(), GLVertexArray::DrawMode::STATIC, screenQuadVertices.data());
    mquadVAO.enableAttribute(0, 3, sizeof(VertexHolder), nullptr);
    mquadVAO.enableAttribute(1, 2, sizeof(VertexHolder), reinterpret_cast<void*>(offsetof(VertexHolder, TexCoords)));

	const std::array<float, 108> vertices{
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glGenVertexArrays(1, &mCubeVAO);
	glBindVertexArray(mCubeVAO);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	// environment map FBO
	glGenFramebuffers(1, &mEnvCubeMap);
	unsigned int envMapRBO;
	glGenRenderbuffers(1, &envMapRBO);

	glBindFramebuffer(GL_FRAMEBUFFER, mEnvCubeMap);
	glBindRenderbuffer(GL_RENDERBUFFER, envMapRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, res, res);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, envMapRBO);

	// TODO : Render the hdrTexture using texture frame buffers
	// bind textures to the frame buffer
	// glTexImage2D - for the skybox
	// setup projection and view matrices for capturing data onto the 6 cubemap face directions
}