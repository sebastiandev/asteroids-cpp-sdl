#include "SDL.h"
#include "SDL_mixer.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <ostream>


class Mixer
{
public:
	Mixer();
	//Mixer(int audio_rate, Uint16 audio_format,int audio_channels,int audio_buffers);
	void playMusic(char* path);
	void playEffect(std::string type);
	void volumeControl(int);
	virtual ~Mixer();
	void setAudio_rate(int);
	void setAudio_format(Uint16);
	void setAudio_channels(int);
	void setAudio_buffers(int);
	void setMusic(Mix_Music*);
	Mix_Music* getMusic();
	int getAudio_rate();
	Uint16 getAudio_format();
	int getAudio_buffers();
	int getAudio_channels();
	void freeChannelOne();

private:
	int audio_rate;
	Uint16 audio_format; /* 16-bit stereo */
	int audio_channels;
	int audio_buffers;
	Mix_Music* music;
	Mix_Chunk *sound;
	int channel;
};