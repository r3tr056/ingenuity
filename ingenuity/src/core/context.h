#pragma once

#include <string>
#include <memory>

namespace ingenuity {
	namespace gfx {}
	namespace core {

		namespace core = ingenuity::core;
		namespace gfx = ingenuity::gfx;

		class Context {
		public:
			Context(const std::string& projectPath, const std::string& projectName);
			~Context();

			void ResetProjectSettings();
			void IsProjectSettingsIntegrityVerified();
			void ApplyProjectSettings();

		public:
			const std::string m_projectPath;
			const std::string m_projectName;
			const std::string m_projectFilePath;
			const std::string m_engineAssetsPath;
			const std::string m_projectAssetsPath;
			const std::string m_projectScriptsPath;
			const std::string m_editorAssetsPath;

			std::unique_ptr<core::Context::Device> device;
			std::unique_ptr<gfx::Window> window;
			std::unique_ptr<input::InputManager> inputManager;
			std::unique_ptr<core::Context::Driver> driver;
			std::unique_ptr<core::ECS::Renderer> renderer;
			std::unique_ptr<core::ShapeDrawer> shapeDrawer;
		};
} }