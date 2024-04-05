#pragma once

#include <memory>
#include <string>
#include <vector>

namespace finity {
namespace audio {
	class DeviceImpl;

	/// <summary>
	/// Wrapper over the audio device and the audio context. Can enumerate ans query device properties
	/// </summary>
	class AudioDevice {
	public:
		AudioDevice(int devnum = 0) : impl_(std::make_unique<DeviceImpl>(devnum)) {}
		~AudioDevice() = default;

		void enable() { if (impl_) { impl_->enable(); } }
		void disable();
		bool is_valid();
		const std::string& get_device_id() const;
		const std::string& get_vendor() const;
		const std::string& get_version() const;
		const std::string& get_extensions() const;
		static std::vector<std::string> enumerate_playback_devs();
		static std::vector<std::string> enumerate_capture_devs();

	private:
		std::unique_ptr<DeviceImpl> impl_;
	};
}
}