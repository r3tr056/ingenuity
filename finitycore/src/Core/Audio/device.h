#pragma once

#include <memory>
#include <cstring>
#include <vector>
#include <cstdint>
#include <sstream>
#include <AL/alc.h>
#include <AL/alext.h>

namespace finAudio {
	namespace device {
		class DeviceImpl {
		public:
			DeviceImpl(int devnum);
			~DeviceImpl() = default;

			void enable();
			void disable();

			bool is_valid() const;

			const std::string& get_dev_id() const;
			const std::string& get_version() const;
			const std::string& get_vendor() const;
			const std::string& get_exts() const;

			static std::vector<std::string> enumerate_playback_devs();
			static std::vector<std::string> enumerate_capture_devs();

		private:
			struct deleter {
				void operator()(ALCdevice* obj);
				void operator()(ALCcontext* obj);
			};

			std::unique_ptr<ALCdevice, deleter> device_;
			std::unique_ptr<ALCcontext, deleter> context_;

			std::string device_id_;

			std::string version_;
			std::string vendor_;
			std::string extensions_;
		};
	}
}
