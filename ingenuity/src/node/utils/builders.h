#pragma once

#include <imgui_node_editor.h>

using namespace ax::NodeEditor;

namespace ingenuity { namespace NodeEditor { namespace Utils {

	struct BlueprintNodeBuilder {
		BlueprintNodeBuilder(ImTextureID texture = nullptr, int texWidth = 0, int texHeight = 0);

		void Begin(NodeId id);
		void End();

		void Header(const ImVec4& color = ImVec4(1, 1, 1, 1));
		void EndHeader();

		void Input(PinId id);
		void EndInput();

		void Middle();

		void Output(PinId id);
		void EndOutput();

	private:
		enum class Stage {
			Invalid,
			Begin,
			Header,
			Content,
			Input,
			Output,
			Middle,
			End
		};

		bool SetStage(Stage stage);

		void Pin(PinId id, PinKind kind);
		void EndPin();

		ImTextureID headerTextureId;
		int headerTextureWidth;
		int headerTextureHeight;
		NodeId currentNodeId;
		Stage currentStage;
		ImU32 headerColor;
		ImVec2 nodeMin;
		ImVec2 nodeMax;
		ImVec2 headerMin;
		ImVec2 headerMax;
		ImVec2 contentMin;
		ImVec2 contentMax;
		bool hasHeader;
	};

} // namespace utils 
} // namespace NodeEditor 
} // namespace ingenuity