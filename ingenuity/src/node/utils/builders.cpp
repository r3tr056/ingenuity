
#include "builders.h"

# define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

namespace axed = ax::NodeEditor;
namespace edUtil = ingenuity::NodeEditor::Utils;

edUtil::BlueprintNodeBuilder::BlueprintNodeBuilder(ImTextureID texture, int texWidth, int texHeight) : headerTextureId(texture), headerTextureWidth(texWidth), headerTextureHeight(texHeight), currentNodeId(0), currentStage(Stage::Invalid), hasHeader(false)
{
}

void edUtil::BlueprintNodeBuilder::Begin(NodeId id)
{
	hasHeader = false;
	headerMin = headerMax = ImVec2();

	axed::PushStyleVar(StyleVar_NodePadding, ImVec4(8, 4, 8, 8));
	axed::BeginNode(id);
	ImGui::PushID(id.AsPointer());
	currentNodeId = id;
	SetStage(Stage::Begin);
}

void edUtil::BlueprintNodeBuilder::End() {
	SetStage(Stage::End);
	axed::EndNode();

	if (ImGui::IsItemVisible()) {
		auto alpha = static_cast<int>(255 * ImGui::GetStyle().Alpha);
		auto drawList = axed::GetNodeBackgroundDrawList(currentNodeId);
		const auto halfBorderWidth = axed::GetStyle().NodeBorderWidth * 0.5f;
		auto HeaderColor = IM_COL32(0, 0, 0, alpha) | (headerColor & IM_COL32(255, 255, 255, 0));

		if ((headerMax.x > headerMin.x) && (headerMax.y > headerMin.y) && headerTextureId) {
			const auto uv = ImVec2(
				(headerMax.x - headerMin.x) / (float)(4.0f * headerTextureWidth),
				(headerMax.y - headerMin.y) / (float)(4.0f * headerTextureHeight)
			);

			drawList->AddImageRounded(headerTextureId,
				headerMin - ImVec2(8 - halfBorderWidth, 4 - halfBorderWidth),
				headerMax + ImVec2(8 - halfBorderWidth, 0),
				ImVec2(0.0f, 0.0f), uv,
				HeaderColor, GetStyle().NodeRounding, 1 | 2);
			
			auto headerSeperatorMin = ImVec2(headerMin.x, headerMax.y);
			auto headerSeperatorMax = ImVec2(headerMax.x, headerMin.y);

			if ((headerSeperatorMax.x > headerSeperatorMin.x) && (headerSeperatorMax.y > headerSeperatorMin.y)) {
				drawList->AddLine(
					headerSeperatorMin + ImVec2(-(8 - halfBorderWidth), -0.5f),
					headerSeperatorMax + ImVec2((8 - halfBorderWidth), -0.5f),
					ImColor(255, 255, 255, 96 * alpha / (3 * 255)), 1.0f);
			}
		}
	}
	currentNodeId = 0;
	ImGui::PopID();
	axed::PopStyleVar();
	SetStage(Stage::Invalid);
}

void edUtil::BlueprintNodeBuilder::Header(const ImVec4& color) {
	headerColor = ImColor(color);
	SetStage(Stage::Header);
}

void edUtil::BlueprintNodeBuilder::EndHeader() {
	SetStage(Stage::Content);
}

void edUtil::BlueprintNodeBuilder::Input(PinId id) {
	if (currentStage == Stage::Begin) {
		SetStage(Stage::Content);
	}

	const auto applyPadding = (currentStage == Stage::Input);
	SetStage(Stage::Input);
	if (applyPadding) {
		ImGui::Spring(0);
	}
	Pin(id, PinKind::Input);
	ImGui::BeginHorizontal(id.AsPointer());
}

void edUtil::BlueprintNodeBuilder::EndInput() {
	ImGui::EndHorizontal();
	EndPin();
}

void edUtil::BlueprintNodeBuilder::Middle() {
	if (currentStage == Stage::Begin) {
		SetStage(Stage::Content);
	}
	SetStage(Stage::Middle);
}

void edUtil::BlueprintNodeBuilder::Output(PinId id) {
	if (currentStage == Stage::Begin) {
		SetStage(Stage::Content);
	}
	const auto applyPadding = (currentStage == Stage::Output);
	SetStage(Stage::Output);
	if (applyPadding) {
		ImGui::Spring(0);
	}
	Pin(id, PinKind::Output);
	ImGui::BeginHorizontal(id.AsPointer());
}

void edUtil::BlueprintNodeBuilder::EndOutput() {
	ImGui::EndHorizontal();
	EndPin();
}

bool edUtil::BlueprintNodeBuilder::SetStage(Stage stage) {
	if (stage == currentStage) {
		return false;
	}
	auto oldStage = currentStage;
	currentStage = stage;

	ImVec2 cursor;
	switch (oldStage)
	{
	case Stage::Invalid:
		break;
	case Stage::Begin:
		break;

	case Stage::Header:
		ImGui::EndHorizontal();
		headerMin = ImGui::GetItemRectMin();
		headerMax = ImGui::GetItemRectMax();
		// spacing between header and content
		ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.y * 2.0f);
		break;

	case Stage::Content:
		break;

	case Stage::Input:
		axed::PopStyleVar(2);
		ImGui::Spring(1, 0);
		ImGui::EndVertical();
		// #debug
		ImGui::GetWindowDrawList()->AddRect(
			ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 0, 255));
		break;

	case Stage::Output:
		axed::PopStyleVar(2);
		ImGui::Spring(1, 0);
		ImGui::EndVertical();
		break;

	case Stage::Middle:
		ImGui::EndVertical();
		// #debug
		ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 0, 255));
		break;

	case Stage::End:
		break;
	}

	switch (stage)
	{
	case Stage::Begin:
		ImGui::BeginVertical("node");
		break;

	case Stage::Header:
		hasHeader = true;
		ImGui::BeginHorizontal("header");
		break;

	case Stage::Content:
		if (oldStage == Stage::Begin) {
			ImGui::Spring(0);
		}
		ImGui::BeginHorizontal("content");
		ImGui::Spring(0, 0);
		break;

	case Stage::Input:
		ImGui::BeginVertical("inputs", ImVec2(0, 0), 0.0f);
		axed::PushStyleVar(axed::StyleVar_PivotAlignment, ImVec2(0, 0.5f));
		axed::PushStyleVar(axed::StyleVar_PivotSize, ImVec2(0, 0));
		if (!hasHeader) {
			ImGui::Spring(1, 0);
		}
		break;

	case Stage::Middle:
		ImGui::Spring(1);
		ImGui::BeginVertical("middle", ImVec2(0, 0), 1.0f);
		break;

	case Stage::Output:
		if (oldStage == Stage::Middle || oldStage == Stage::Input) {
			ImGui::Spring(1);
		}
		else {
			ImGui::Spring(1, 0);
		}
		ImGui::BeginVertical("outputs", ImVec2(0, 0), 1.0f);
		axed::PushStyleVar(axed::StyleVar_PivotAlignment, ImVec2(1.0f, 0.5f));
		axed::PushStyleVar(axed::StyleVar_PivotSize, ImVec2(0, 0));

		if (!hasHeader) {
			ImGui::Spring(1, 0);
		}
		break;

	case Stage::End:
		if (oldStage == Stage::Input) {
			ImGui::Spring(1, 0);
		}
		if (oldStage != Stage::Begin) {
			ImGui::EndHorizontal();
		}
		contentMin = ImGui::GetItemRectMin();
		contentMax = ImGui::GetItemRectMax();
		break;

	case Stage::Invalid:
		break;

	default:
		break;
	}
}

void edUtil::BlueprintNodeBuilder::Pin(PinId id, PinKind kind) {
	axed::BeginPin(id, kind);
}

void edUtil::BlueprintNodeBuilder::EndPin() {
	axed::EndPin();
}