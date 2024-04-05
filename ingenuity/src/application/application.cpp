
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <algorithm>
#include <cstdint>

#include "application.h"

#define STB_IMAGE_IMPLEMENTATION
extern "C" {
#include <image/stb_image.h>
}


namespace ingenuity {
	namespace core {
		static void application_error_callback(int error, const char* description)
		{
			fprintf(stderr, "Error %d: %s\n", error, description);
		}

		Application::Application(const std::string& projectPath, const std::string& projectName, const char* glsl_version)
		{			
		}

		Application::~Application()
		{
		}

		void Application::Run()
		{
			is_running = true;

		}

		bool Application::isRunning() const
		{
			return is_running;
		}

		ImTextureID Application::LoadTexture(const char* path)
		{
			int width = 0, height = 0, component = 0;
			if (auto data = stbi_load(path, &width, &height, &component, 4))
			{
				auto texture = Application::CreateTexture(data, width, height);
				stbi_image_free(data);
				return texture;
			}
			else
				return nullptr;
		}

		ImTextureID Application::CreateTexture(const void* data, int width, int height)
		{
			g_Textures.resize(g_Textures.size() + 1);
			ImTexture& texture = g_Textures.back();

			// Upload texture to graphics system
			GLint last_texture = 0;
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
			glGenTextures(1, &texture.TextureID);
			glBindTexture(GL_TEXTURE_2D, texture.TextureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glBindTexture(GL_TEXTURE_2D, last_texture);

			texture.Width = width;
			texture.Height = height;

			return reinterpret_cast<ImTextureID>(static_cast<std::intptr_t>(texture.TextureID));
		}

		std::vector<ImTexture>::iterator Application::FindTexture(ImTextureID texture)
		{
			auto textureID = static_cast<GLuint>(reinterpret_cast<std::intptr_t>(texture));

			return std::find_if(g_Textures.begin(), g_Textures.end(), [textureID](ImTexture& texture)
				{
					return texture.TextureID == textureID;
				});
		}

		void Application::DestroyTexture(ImTextureID texture)
		{
			auto textureIt = Application::FindTexture(texture);
			if (textureIt == g_Textures.end())
				return;

			glDeleteTextures(1, &textureIt->TextureID);

			g_Textures.erase(textureIt);
		}

		int Application::GetTextureWidth(ImTextureID texture)
		{
			auto textureIt = Application::FindTexture(texture);
			if (textureIt != g_Textures.end())
				return textureIt->Width;
			return 0;
		}

		int Application::GetTextureHeight(ImTextureID texture)
		{
			auto textureIt = Application::FindTexture(texture);
			if (textureIt != g_Textures.end())
				return textureIt->Height;
			return 0;
		}
	}
}
