#pragma once

#include <string>

namespace ingenuity { namespace hardware { class HardwareInfo; } }

namespace ingenuity {
	namespace ui {
		namespace panels {

			class HardwareInfo {
			public:
				HardwareInfo(const std::string& p_title, bool opened, const Settings::PanelSettings& p_panelSettings, float logFrequency, size_t maxElements);
				~HardwareInfo();

				void Update(float deltaTime);

			private:
				float m_updateTimer = 0.0f;
				float m_logFrequency;
				size_t m_maxElements;
				APlot* m_cpuUsage;
				APlot* m_gpuUsage;
				APlot* m_ramUsage;

			};
		}
	}
}