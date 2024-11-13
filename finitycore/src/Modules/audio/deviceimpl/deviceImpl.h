#pragma once

#include <finPch.h>

#include <memory>
#include <string>
#include <vector>

#include <AL/alc.h>

namespace finity {
namespace audio {
	
	class DeviceImpl {
	public:
		DeviceImpl(int devnum);
		~DeviceImpl() = default;

		void enable();
		void disable();


		const std::string& get_device_id() const;
		const std::string& get_version() const;
		const std::string& get_vendor() const;
		const std::string& get_extensions() const;

		static std::vector<std::string> enumerate_playback_devices();
		static std::vector<std::string> enumerate_capture_devices();

	private:
		struct deleter
		{
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

	class ListenerImpl {
	public:
		void set_volume(float vol);
		void set_pos(const float& pos);
		void set_velocity(const float& velocity);
		void set_orientation(const float& direction, const float& up);
	};
}
}