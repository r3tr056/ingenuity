#pragma once

#include <cstdlib>
#include <cfloat>
#include <array>

namespace finity {
	namespace audio {
		class ListenerImpl {
		public:
			void set_volume(float volume);
			void set_pos(const std::array<float, 3>& position);
			void set_velocity(const std::array<float, 3>& velocity);
			void set_orientation(const std::array<float, 3>& direction, const std::array<float, 3>& up);
		};
	}
}