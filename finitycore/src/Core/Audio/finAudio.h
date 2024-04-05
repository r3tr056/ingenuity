#pragma once

#ifndef __FIN_AUDIO_H__
#define __FIN_AUDIO_H__

#include "../../modules/finModule.h"
#include <list>

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class finAudio : finModule {
public:
	finAudio();
	virtual ~finAudio();

	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);
	bool StopMusic();
	bool ResumeMusic();
	bool VolumeMusic(int volume = 128);
	void FadeMusic(int ms);

	void StopFx(int id);
	unsigned int LoadFX(const char* path);
	bool PlayFX(unsigned int fx, int repeat = 0);

private:
	_Mix_Music* music = nullptr;
	std::list < Mix_Chunk*> fx;
};

#endif // !__FIN_AUDIO_H__
