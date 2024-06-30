#include "Camera.h"

using namespace finitycore::Core::Graphics::Components;

bool PrespectiveCamera::init(GLint screenWidth, GLint screenHeight, GLfloat fovRadians, GLfloat depth) {
	mProjection = glm::perspective((float)fovRadians, (float)screenWidth / (float)screenHeight, 1.0f, depth);
	mView = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	return true;
}

void PrespectiveCamera::update(GLint projectionViewBinding, glm::vec3 camPosition, glm::vec3 camLookAt) {
	mView = glm::lookAt(camPosition, camLookAt, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mProjectionView = mProjection * mView;
	glUniformMatrix4fv(projectionViewBinding, 1, GL_FALSE, glm::value_ptr(mProjectionView));
}

glm::mat4 PrespectiveCamera::getPojectionView() {
	return mProjection * mView;
}

bool OrthoCamera::init(GLfloat width, GLfloat height, GLfloat minDepth, GLfloat maxDepth) {
	mProjection = glm::ortho(-width, width, -height, height, minDepth, maxDepth);
	mView = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	return true;
}

void OrthoCamera::update(GLint projectionViewBinding, glm::vec3 camPos, glm::vec3 camLootAt) {
	mView = glm::lookAt(camPos, camLootAt, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mProjectionView = mProjectionView * mView;
	glUniformMatrix4fv(projectionViewBinding, 1, GL_FALSE, glm::value_ptr(mProjectionView));
}

glm::mat4 OrthoCamera::getProjectionView() {
	return mProjection * mView;
}