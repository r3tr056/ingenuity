#pragma once

#include <string>
#include <memory>

namespace finitycore::Core {

	class Context {
	public:
		// Constructor
		Context();

		// Destructor
		~Context();

	public:
		const std::string engineAssetsPath;
		const std::string projectAssetsPath;
		const std::string projectsScriptsPath;

		std::unique_ptr<finitycore::Core::Platform::Device> device;
		std::unique_ptr<finitycore::UIGFX::Window> window;
		std::unique_ptr<finitycore::Core::Platform::InputManager> inputMgr;
		std::unique_ptr<finitycore::Core::Platform::Driver> driver;
		std::unique_ptr<finitycore::Graphics::Renderer> renderer;
		std::unique_ptr<finitycore::UIGFX::UIManager> uiMgr;

		std::unique_ptr<finitycore::Physx::PhysicsEngine> physicsEng;

		std::unique_ptr<finitycore::Core::Platform::AudioPlayer> audioPlayer;
		std::unique_ptr<finitycore::Core::Audio::AudioEngine> audioEng;

		std::unique_ptr<finitycore::Scripting::ScriptInterpreter> scriptInterpreter;

		std::unique_ptr<finitycore::Graphics::Buffers::UnformBuffer> engineUBO;
		std::unique_ptr<finitycore::Graphics::Buffers::ShaderStorageBuffer> lightSSBO;

		finitycore::Core::SceneSystem::SceneManager sceneMgr;

		finitycore::Core::ResManagement::ModelManager modelMgr;
		finitycore::Core::ResManagement::TextureManager textureMgr;
		finitycore::Core::ResManagement::ShaderManager shaderMgr;
		finitycore::Core::ResManagement::MaterialManager matMgr;
		finitycore::Core::ResManagement::SoundManager soungMgr;

		finitycore::Core::Platform::IniFile projectSettings;
	};
}