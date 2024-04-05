#pragma once

#include <cstdint>
#include "./context.h"

namespace ingenuity {
	namespace core {

		class Editor {
		public:
			Editor(Context& context);
			~Editor();

			void SetupUI();
			void PreUpdate();
			void Update(float deltaTime);
			void handleGlobalShortcuts();
			void UpdateCurrentEditorMode(float deltaTime);
			void UpdatePlayMode(float deltaTime);
			void UpdateEditMode(float deltaTime);
			void UpdateEditorPanels(float deltaTime);
			void PrepRendering(float deltaTime);
			void RenderViews(float deltaTime);
			void RenderEditorUI(float deltaTime);
			void PostUpdate();

		private:
			uint64_t m_elapsedFrames = 0;
			Canvas m_Canvas;
			Context& m_Context;
			EditorRanderer m_editorRenderer;
			PanelsManager m_panelsManager;
			EditorActions m_editorActions;

		};
} }