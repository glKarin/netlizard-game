#ifndef KARIN_SDLK_SOUND_H
#define KARIN_SDLK_SOUND_H

#include <SDL/SDL_mixer.h>

int SDLK_Init(void);
void SDLK_Exit(void);
int SDLK_HasInit(void);

int SDLK_PlayMusic(Mix_Music *music);
int SDLK_PlaySound(int channel, Mix_Chunk *sound);

Mix_Music * SDLK_LoadMusic(const char *file);
Mix_Chunk * SDLK_LoadSound(const char *file);

void SDLK_FreeMusic(Mix_Music *music);
void SDLK_FreeSound(int channel, Mix_Chunk *sound);

int SDLK_PauseMusic(void);
int SDLK_PauseSound(int channel);

int SDLK_ResumeSound(int channel);
int SDLK_SoundIsPlaying(int channel);

#endif
