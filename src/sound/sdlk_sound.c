#include "sdlk_sound.h"

#include <SDL/SDL.h>

static int sdlk_has_init = 0;

const int freq = MIX_DEFAULT_FREQUENCY;
const Uint16 format = MIX_DEFAULT_FORMAT;
const int channel = MIX_DEFAULT_CHANNELS;
const int chunk_size = 512;

int SDLK_Init(void)
{
	if(sdlk_has_init)
		return 1;
	if(SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		fprintf(stderr, "%s\n", SDL_GetError());
		return 0;
	}
	if(Mix_OpenAudio(freq, format, channel, chunk_size) != 0)
	{
		fprintf(stderr, "%s\n", Mix_GetError());
		return 0;
	}
	sdlk_has_init = 1;
	return 1;
}

void SDLK_Exit(void)
{
	if(!sdlk_has_init)
		return;
	Mix_CloseAudio();
	SDL_Quit();
}

Mix_Music * SDLK_LoadMusic(const char *file)
{
	if(!sdlk_has_init)
		return NULL;
	if(!file)
		return NULL;
	Mix_Music *music = Mix_LoadMUS(file);
	if(!music)		
	{
		fprintf(stderr, "%s\n", Mix_GetError());
		return NULL;
	}
	return music;
}

int SDLK_PlayMusic(Mix_Music *music)
{
	if(!sdlk_has_init)
		return 0;
	if(!music)
		return 0;
	if(Mix_PlayingMusic())
		return 1;
	if(Mix_PlayMusic(music, -1) != 0)
	{
		fprintf(stderr, "%s\n", Mix_GetError());
		return 0;
	}
	return 1;
}

int SDLK_HasInit(void)
{
	return sdlk_has_init;
}

void SDLK_FreeMusic(Mix_Music *music)
{
	if(!sdlk_has_init)
		return;
	if(!music)
		return;
	Mix_HaltMusic();
	Mix_FreeMusic(music);
}

Mix_Chunk * SDLK_LoadSound(const char *file)
{
	if(!sdlk_has_init)
		return NULL;
	if(!file)
		return NULL;
	Mix_Chunk *sound = Mix_LoadWAV(file);
	if(!sound)		
	{
		fprintf(stderr, "%s\n", Mix_GetError());
		return NULL;
	}
	return sound;
}

void SDLK_FreeSound(int channel, Mix_Chunk *sound)
{
	if(!sdlk_has_init)
		return;
	if(!sound)
		return;
	Mix_HaltChannel(channel);
	Mix_FreeChunk(sound);
}

int SDLK_PauseMusic(void)
{
	if(!sdlk_has_init)
		return 0;
	if(Mix_PlayingMusic() == 0)
		return 1;
	Mix_PauseMusic();
	return 1;
}

int SDLK_PlaySound(int channel, Mix_Chunk *sound)
{
	if(!sdlk_has_init)
		return 0;
	if(!sound)
		return 0;
	if(Mix_Playing(channel))
		return 1;
	if(Mix_PlayChannel(channel, sound, 0) == -1)
	{
		fprintf(stderr, "%s\n", Mix_GetError());
		return 0;
	}
	return 1;
}

int SDLK_PauseSound(int channel)
{
	if(!sdlk_has_init)
		return 0;
	if(Mix_Playing(channel) == 0)
		return 1;
	Mix_Pause(channel);
	return 1;
}

int SDLK_ResumeSound(int channel)
{
	if(!sdlk_has_init)
		return 0;
	Mix_Resume(channel);
	return 1;
}

int SDLK_SoundIsPlaying(int channel)
{
	if(!sdlk_has_init)
		return 0;
	return Mix_Playing(channel);
}
