#include <assert.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "AL/al.h"
#include "AL/alc.h"

#define NUM_BUFFERS 4
#define BUFFER_SAMPLES 8192

class SourceImpl {
public:
	using native_handle_type = ALuint;
	SourceImpl();
	~SourceImpl();

	SourceImpl(SourceImpl&& rhs) = delete;
	SourceImpl& operator=(SourceImpl&& rhs) = delete;
	SourceImpl(const SourceImpl& rhs) = delete;
	SourceImpl& operator=(const SourceImpl& rhs) = delete;

	bool create();
	bool bind(SourceImpl* sound);
	bool has_binded_sound() const;
	void unbind();
	void purge();

	void set_loop(bool on);
	void set_volume(float volume);
	void set_pitch(float pitch);
	void set_pos(const float& pos);
	void set_velocity(const float& velocity)
};