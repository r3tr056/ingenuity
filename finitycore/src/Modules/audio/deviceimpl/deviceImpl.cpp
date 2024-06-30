#include "deviceImpl.h"
#include "AL/al.h"
#include "AL/alext.h"
#include <sstream>
#include "..\..\..\core\audio\device.h"

namespace finity {
	namespace audio {
		namespace openal {
			static bool al_has_extension(ALCdevice* dev, const char* ext) {
				return (alcIsExtensionPresent(dev, ext) == AL_TRUE);
			}

			static std::vector<std::string> al_get_strings(ALCdevice * dev, ALenum e) {
				std::vector<std::string> result;
				auto devs = reinterpret_cast<const char*>(alcGetString(dev, e));

				while (!std::string(devs).empty()) {
					result.emplace_back(devs);
					devs += result.back().size() + 1;
				}
				return result;
			}

			static std::string al_version() {
				std::stringstream ss;
				auto version = alGetString(AL_VERSION);
				if (version != nullptr) {
					ss << "OpenAL version: " << version;
				}
				return ss.str();
			}

			static std::string al_vendor() {
				std::stringstream ss;
				auto vendor = alGetString(AL_VERSION);
				if (vendor != nullptr) {
					ss << "OpenAL vendor: " << vendor;
				}
				return ss.str();
			}

			static std::string al_extensions() {
				std::stringstream ss;
				auto extensions = alGetString(AL_EXTENSIONS);
				if (extensions != nullptr) {
					ss << "OpenAL extensions: " << extensions;
				}
				return ss.str();
			}

		}

		DeviceImpl::DeviceImpl(int devnum) {

			auto playback_devs = enumerate_playback_devices();
			log_info("Supported audio playback devices : ");
			for (const auto& dev : playback_devs) {
				log_info("-- " + dev)
			}
			auto cap_devices = enumerate_capture_devices();
			log_info("Supported capture devices : ");
			for (const auto& dev : cap_devices) {
				log_info("-- " + dev)
			}

			if (devnum >= 0 && devnum < int(playback_devs.size())) {
				device_id_ = playback_devs[std::size_t(devnum)];
			}

			// Select a device
			device_.reset(alcOpenDevice(device_id_.empty() ? nullptr : device_id_.c_str()));

			if (device_ == nullptr) {
				log_error("Can't open audio playback device: " + device_id_);
				std::runtime_error("Failed to open audio playback device : " + device_id_);
			}
			bool has_efx_ = openal::al_has_extension(device_.get(), "ALC_EXT_EFX");

			ALint attribs[4] = { 0 };
			attribs[0] = ALC_MAX_AUXILIARY_SENDS;
			attribs[1] = 4;

			// create a context
			context_.reset(alcCreateContext(device_.get(), has_efx_ ? attribs : nullptr));

			if (context_ == nullptr) {
				log_error("Cant create audio context for playback device: " + device_id_);
				throw std::runtime_error("Cant create audio context for playback device: " + device_id_);
			}
			enable();

			version_ = openal::al_version();
			vendor_ = openal::al_vendor();
			extensions_ = openal::al_extensions();

			log_info(version_);
			log_info(vendor_);
			log_info(extensions_);
			log_info("Using audio playback device: " + device_id_);
		}

		void DeviceImpl::enable()
		{
			// set the ALC context
			alcMakeContextCurrent(context_.get());
		}

		void DeviceImpl::disable()
		{
			// unset the ALC context
			alcMakeContextCurrent(nullptr);
		}

		std::vector<std::string> DeviceImpl::enumerate_capture_devices() {
			bool can_enum = openal::al_has_extension(nullptr, "ALC_ENUMERATION_EXT");
			if (can_enum) {
				return openal::al_get_strings(nullptr, ALC_CAPTURE_DEVICE_SPECIFIER);
			}
			return {};
		}

		std::vector<std::string> DeviceImpl::enumerate_playback_devices() {
			bool can_enum = openal::al_has_extension(nullptr, "ALC_ENUMERATION_EXT");
			if (can_enum) {
				return openal::al_get_strings(nullptr, ALC_ALL_DEVICES_SPECIFIER);
			}
			return {};
		}

		void DeviceImpl::deleter::operator()(ALCcontext* obj)
		{
			if (obj != nullptr)
			{
				alcMakeContextCurrent(nullptr);
				alcDestroyContext(obj);
			}
		}

		void DeviceImpl::deleter::operator()(ALCdevice* obj) {
			if (obj != nullptr) {
				alcCloseDevice(obj);
			}
		}

		void ListenerImpl::set_volume(float vol) {
		}

		void ListenerImpl::set_pos(float pos) {
		
		}
	}
}