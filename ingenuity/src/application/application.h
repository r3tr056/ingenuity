#pragma once

#include <string>
#include "../core/context.h"
#include "../core/editor.h"


namespace ingenuity {
	namespace core {
		struct ImTexture
		{
			GLuint TextureID = 0;
			int    Width = 0;
			int    Height = 0;
		};

		class Application {
		public:
			Application(const std::string& projectPath, const std::string& projectName, const char* glsl_version);
			~Application();
			
			void Run();
			bool isRunning() const;

		private:
			Context mContext;
			Editor mEditor;
			static std::vector<ImTexture> g_Textures;
			bool is_running;

			ImTextureID LoadTexture(const char* path);
			ImTextureID CreateTexture(const void* data, int width, int height);
			static std::vector<ImTexture>::iterator FindTexture(ImTextureID texture);
			void DestroyTexture(ImTextureID texture);
			int GetTextureWidth(ImTextureID texture);
			int GetTextureHeight(ImTextureID texture);
		};
	}
}