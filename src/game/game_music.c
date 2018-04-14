#include "game_music.h"
#include "sdlk_sound.h"

#include "netlizard/netlizard_3d.h"
#include "netlizard/media_util.h"

#define ALIEN_SHOOTER_3D_MM_MID _KARIN_RESOURCE_DIR"resource/mm.mid"

static Mix_Music *music = NULL;
static int music_of_game = -2;

int Sound_LoadMenuMusic(int game)
{
	if(music_of_game == game)
		return 0;
	if(music)
	{
		Sound_StopMusic();
		Sound_FreeMusic();
		music = NULL;
	}
	music_of_game = game;
	if(music_of_game == -2)
		return 0;

	char *file = NULL;
	if(music_of_game == -1)
		file = strdup(ALIEN_SHOOTER_3D_MM_MID);
	else
		file = nlGetMenuMusicFilePath(music_of_game);
	//printfs(file);
	if(!file)
		return 0;
	music = SDLK_LoadMusic(file);
	free(file);
	return(music != NULL ? 1 : 0);
}

void Sound_PlayMusic(void)
{
	if(!music)
		return;
	SDLK_PlayMusic(music);
}

void Sound_StopMusic(void)
{
	if(!music)
		return;
	SDLK_PauseMusic();
}

void Sound_FreeMusic(void)
{
	if(!music)
		return;
	SDLK_FreeMusic(music);
}

int Sound_LoadLevelMusic(int game, int level)
{
	if(music)
	{
		Sound_StopMusic();
		Sound_FreeMusic();
		music = NULL;
	}
	char *file = nlGetLevelMusicFilePath(game, level);
	//printfs(file);
	if(!file)
		return 0;
	music = SDLK_LoadMusic(file);
	free(file);
	return(music != NULL ? 1 : 0);
}

