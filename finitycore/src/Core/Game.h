#pragma once

#include "UIGFX/Canvas.h"
#include "Context.h"


#include "Debug/FPSCounter.h"

#ifdef _DEBUG
#include "Debug/DriverInfo.h"
#include "Debug/GameProfiler.h"
#include "Debug/FrameInfo.h"
#endif

namespace finitycore::Core {

	class Game {
	public:
		Game(Context& p_context);

		~Game();

		void PreUpdate();

		void Update(float p_dT);

		void PostUpdate();

	private:
		float m_elapsed = 0.0f;

		Context& m_context;
		Canvas m_canvas;

		Renderer m_gameRenderer;
		FPSCounter m_fpsCounter;

#ifdef _DEBUG
		DriverInfo m_driverInfo;
		GameProfiler m_gameProfiler;
		FrameInfo m_frameInfo;
#endif

#ifdef _DEBUG
		bool m_showDebugInformation = true;
#else
		bool m_showDebugInformation = false;
#endif

	};

}