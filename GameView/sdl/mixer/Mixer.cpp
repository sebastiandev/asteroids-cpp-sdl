#include "Mixer.h"

Mixer::Mixer(void)
{	
	SDL_Init(SDL_INIT_EVERYTHING);
	audio_rate= 44100;
	audio_channels = 2;
	audio_format = AUDIO_S16;
	audio_buffers = 1024;
	music = NULL;
	channel = NULL;
	sound= NULL;
	/*this->explosion = Mix_LoadWAV("..\\sounds\\colision.wav");
	this->misil = Mix_LoadWAV("..\\sounds\\bala.wav");
	this->choque = Mix_LoadWAV("..\\sounds\\colision.wav");
	bala = Mix_LoadWAV("..\\sounds\\bala.wav");*/
}

Mixer::~Mixer()
{	
	Mix_CloseAudio();
	Mix_FreeMusic(music);  
}

void Mixer::playMusic(char* path)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	int rate = this->audio_rate;
	Uint16 format = this->audio_format;
	int channel = this->audio_channels;
	int buffer = this->audio_buffers;
	
	if(Mix_OpenAudio(rate,format,channel, buffer)) 
    {
		exit(1);
	}
	Mix_Music* aux = Mix_LoadMUS (path);
	setMusic(aux);
	Mix_PlayMusic ( this->music, -1 ); //reproduccion infinita

}

void Mixer::setMusic(Mix_Music* newMusic)
{
	this->music = newMusic;
}

Mix_Music* Mixer::getMusic()
{
	return this->music;
}

void Mixer::playEffect(std::string type)
{
	int volumen = 100;
    Mix_AllocateChannels(5);
	if(Mix_OpenAudio(audio_rate,audio_format,audio_channels, audio_buffers)) 
    {
		exit(1);
	}
	if(type == "BALA" || type == "MISIL")
	{
		
		this->sound = Mix_LoadWAV("..\\sounds\\bala.wav");
		Mix_VolumeChunk(sound, volumen);
		this-> channel = Mix_PlayChannel(1, sound, 0);

	}
	if(type == "COLISION" || type == "CHOQUE")
	{
		Mix_Chunk *sonido = Mix_LoadWAV("..\\sounds\\colision.wav");
		Mix_VolumeChunk(sonido, volumen);
		this-> channel = Mix_PlayChannel(1, sonido, 0);
	}
			//Mix_FreeChunk(sound);
}

void Mixer::freeChannelOne()
{
	if (this->sound != NULL)
		Mix_FreeChunk(this->sound);
}

void volumeControl(int)
{
}