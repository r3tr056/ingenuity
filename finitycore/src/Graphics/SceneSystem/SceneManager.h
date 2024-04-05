#pragma once

#include "./Scene.h"

namespace finitycore::Core::Graphics::SceneSystem {

	class SceneManager {
	public:
		SceneManager(const std::string& p_sceneRootFolder = "");

		~SceneManager();

		void Update();

		bool LoadScene(const std::string_view& path, bool absoulte = false);

		bool LoadSceneFromMemory(tinyxml2::XMLDocument& scene_doc);

		void UnloadCurrentScene();

		void HasCurrentScene() const;

		void LoadAnyPlayDelayed(const std::string_view& path, bool absolute = false);

		void LoadEmptyScene();

		void LoadEmptyLightedScene(Components::Light& light);

		Scene* GetCurrentScene();

		std::string_view GetCurrentSceneSourcePath() const;

		bool IsCurrentSceneLoadedFromDisk() const;

		void StoreCurrentSceneSourcePath(const std::string_view& path);

		void ForgetCurrentSceneSourcePath();

	public:
		EventBus::Event scene_unloadEvent;
		EventBus::Event scene_loadEvent;
		EventBus::Event<const std::string&> currentsourcepathChangedEvent;

	private:
		const std::string m_sceneRootFolder;
		Scene* m_currentScene;

		bool m_currentSceneLoadedFromDisk = false;
		std::string m_currentScenePath = "";

		std::is_function<void()> m_delayedLoadCall;
	};
}