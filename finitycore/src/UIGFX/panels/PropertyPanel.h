#pragma once

#include "graphics/components/Light.h"
#include "graphics/components/Mesh.h"
#include "gfx/panels/SceneView.h"
#include "gfx/Panel.h"
#include <imgui/imgui.h>
#include "FileBrowser.h"

#include <functional>

class PropertyPanel: public finPanel {
private:
	std::function<void(const std::string&)> mMeshLoadCallback;
	std::string mCurrentFile;
	ImGui::FileBrowser mFileDialog;

public:
	PropertyPanel() {
		mCurrentFile = "< ... >";
		mFileDialog.SetTitle("Open Mesh");
		mFileDialog.SetTypeFilters({ ".fbx", ".obj" });
	}

	void drawPanel(SceneView* sceneView) {
		auto mesh = sceneView->getMesh();
		
		// ImGui Draw Calls
		{
			ImGui::Begin("Properties");
			if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen)) {
				if (ImGui::Button("Open..."))
				{
					mFileDialog.Open();
				}
				ImGui::SameLine(0, 0.5f);
				ImGui::Text(mCurrentFile.c_str());
			}

			if (ImGui::CollapsingHeader("Material") && mesh) {
				ImGui::ColorPicker3("Color", (float*)&mesh->mColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
				ImGui::SliderFloat("Roughness", &mesh->mRoughness, 0.0f, 1.0f);
				ImGui::SliderFloat("Metallic", &mesh->mMetallic, 0.0f, 1.0f);
			}

			if (ImGui::CollapsingHeader("Light")) {
				ImGui::Separator();
				ImGui::Text("Position");
				ImGui::Separator();
				// Get the current scene view light position
				// and draw the light position widget
			}
			ImGui::End();
		}
	
		mFileDialog.Display();
		if (mFileDialog.HasSelected()) {
			auto fPath = mFileDialog.GetSelected().string();
			mCurrentFile = fPath.substr(fPath.find_last_of("/\\") + 1);
			mMeshLoadCallback(fPath);
			mFileDialog.ClearSelected();
		}
	}
	void setMeshLoadCallback(const std::function<void(const std::string&)>& callback) {
		mMeshLoadCallback = callback;
	}
};