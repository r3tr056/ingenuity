#include "listener_impl.h"

#include <array>
#include <cstdint>
#include <AL/al.h>

namespace finity {
	namespace audio {
		void ListenerImpl::set_volume(float volume) {
			al_check(alListenerf(AL_GAIN, volume));
		}

		void ListenerImpl::set_pos(const std::array<float, 3>& position) {
			al_check(alListenerfv(AL_POSITION, position.data()));
		}


	}
}