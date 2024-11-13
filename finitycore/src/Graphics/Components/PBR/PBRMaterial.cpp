
#include "PBRMaterial.h"

PBRMaterial::PBRMaterial() : mAlpha(1.0f), mAlphaMaskTexture(0) {
	mMaterialTextures.fill(0);
	mMaterialColors.fill(glm::vec3(1.0f));
}

void PBRMaterial::init(
	const std::string name,
	const std::string albedoPath,
	const std::string aoPath,
	const std::string metallicPath,
	const std::string normalPath,
	const std::string roughnessPath
) {

}