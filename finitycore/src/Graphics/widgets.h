#pragma once

#include "finPch.h"

#include <imgui.h>
#include <imgui_internal.h>

static void draw_vec3_widget(const std::string& label, glm::vec3& values, float columnWidth = 100.0f) {
	ImGuiIO& io = ImGui::GetIO();
	auto boldFont = io.Fonts->Fonts[0];

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
	
	float lineH = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 btnSize = { lineH + 3.0f, lineH };

	ImGui::PushFont(boldFont);
	ImGui::Button("X", btnSize);
	ImGui::PopFont();

	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, 1.0f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushFont(boldFont);
	ImGui::Button("Y", btnSize);
	ImGui::PopFont();

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushFont(boldFont);
	ImGui::Button("Z", btnSize);
	ImGui::PopFont();

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();
}