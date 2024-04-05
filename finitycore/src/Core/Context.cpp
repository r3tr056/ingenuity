#include "Context.h"

finitycore::Core::Context::Context() : engineAssetsPath("Data\\Engine\\"), projectAssetsPath("Data\\User\\Assets\\"), projectsScriptsPath("Data\\User\\Scripts\\"), projectSettings("Data\\User\\Game.ini"), sceneMgr(projectAssetsPath)
{
	ModelManager::ProvideAssetsPaths(projectAssetsPath, engineAssetsPath);
	TextureManager::ProvideAssetsPaths(projectAssetsPath, engineAssetsPath);
	ShaderManager::ProvideAssetsPaths(projectAssetsPath, engineAssetsPath);
	MaterialManager::ProvideAssetsPaths(projectAssetsPath, engineAssetsPath);
	SoundManager::ProvideAssetsPaths(projectAssetsPath, engineAssetsPath);

	// Settings
	UIGFX::Settings::DeviceSettings deviceSettings;
	deviceSettings.contextMajorVersion = projectSettings
}

finitycore::Core::Context::~Context()
{
}
