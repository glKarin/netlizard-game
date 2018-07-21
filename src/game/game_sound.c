#include "game_sound.h"

#include "netlizard/netlizard_3d.h"
#include "sdlk_sound.h"
#include "nl_std.h"
#include "gl_util.h"

#include <math.h>

typedef enum _weapon_sound_type
{
	ct3d_Dagger_sound = 0,
	ct3d_USP_sound,
	ct3d_Python_sound,
	ct3d_Desert_Eagl_sounde,
	ct3d_MP5_sound,
	ct3d_M4a1_sound,
	ct3d_AK47_sound,
	ct3d_D3AU1_sound,
	ct3d_AWP_sound,
	ct3d_Fragmentation_Grenade_sound,
	ct3d_Flash_Grenade_sound,
	specnaz3d_Dagger_sound,
	specnaz3d_Desert_Eagle_sound,
	specnaz3d_MP5_sound,
	specnaz3d_M4a1_sound,
	specnaz3d_AK47_sound,
	specnaz3d_M32_sound,
	specnaz3d_Fragmentation_Grenade_sound,
	egypt3d_Dagger_sound,
	egypt3d_Colt_Walker_sound,
	egypt3d_MP40_sound,
	egypt3d_Mosin_Nagant_sound,
	egypt3d_AK47_sound,
	egypt3d_Plasma_Gun_sound,
	egypt3d_The_Sword_of_Osiris_sound,
	clone3d_Colt_Walker_sound,
	clone3d_SPAS12_sound,
	clone3d_M16_sound,
	clone3d_Rocket_Launcher_sound,
	egypt3d_Worm_Weapon_sound,
	egypt3d_Scorpion_Weapon_sound,
	egypt3d_Fly_Fish_Weapon_sound,
	egypt3d_Anubis_Weapon_sound,
	egypt3d_Tentacle_Weapon_sound,
	egypt3d_Machine_Monster_Weapon_sound,
	egypt3d_Fly_Machine_Weapon_sound,
	clone3d_Machine_Weapon_sound,
	total_weapon_sound_type
} weapon_sound_type;

static const int Channel_Count[total_sound_source_type] = {
	total_weapon_model_type,
	2,
	3,
	3,
	3,
	2
};

typedef struct _game_sound
{
	int channel;
	Mix_Chunk *chunk;
} game_sound;

static game_sound *sounds = NULL;
static int ws_init = 0;

int Sound_LoadGameSound(void)
{
	if(ws_init)
		return 1;
	int count = 0;
	int i;
	for(i = 0; i < total_sound_source_type; i++)
		count += Channel_Count[i];
	sounds = NEW_II(game_sound, count);
	ZERO_II(sounds, game_sound, count);

	for(i = 0; i < count; i++)
	{
		sounds[i].channel = -2;
		sounds[i].chunk = NULL;
	}

	for(i = 0; i < Channel_Count[gun_fire_sound_type]; i++)
		sounds[i].channel = i;

	size_t len = 7;
	const char *f = game_resource_path[nl_contr_terrorism_3d_episode_2];
	if(f)
		len += strlen(f) + 1;
	char *p = NEW_II(char, len);
	for(i = 1; i <= 10; i++)
	{
		if(f)
			sprintf(p, "%s/%d.wav", f, i);
		else
			sprintf(p, "%d.wav", i);
		//printfs(p);
		sounds[ct3d_Dagger + i].chunk = SDLK_LoadSound(p);
	}
	free(p);

	len = 6;
	f = game_resource_path[nl_army_ranger_3d];
	if(f)
		len += strlen(f) + 1;
	p = NEW_II(char, len);
	for(i = 2; i <= 6; i++)
	{
		if(f)
			sprintf(p, "%s/%d.wav", f, i);
		else
			sprintf(p, "%d.wav", i);
		//printfs(p);
		sounds[specnaz3d_Dagger + i - 1].chunk = SDLK_LoadSound(p);
	}
	if(f)
		sprintf(p, "%s/%d.wav", f, 6);
	else
		sprintf(p, "%d.wav", 6);
	//printfs(p);
	sounds[specnaz3d_Fragmentation_Grenade].chunk = SDLK_LoadSound(p);
	free(p);

	len = 6;
	f = game_resource_path[nl_shadow_of_egypt_3d];
	if(f)
		len += strlen(f) + 1;
	p = NEW_II(char, len);
	for(i = 1; i <= 5; i++)
	{
		if(f)
			sprintf(p, "%s/%d.wav", f, i);
		else
			sprintf(p, "%d.wav", i);
		//printfs(p);
		sounds[egypt3d_Dagger + i].chunk = SDLK_LoadSound(p);
	}
	free(p);

	len = 6;
	f = game_resource_path[nl_clone_3d];
	if(f)
		len += strlen(f) + 1;
	p = NEW_II(char, len);
	for(i = 1; i <= 4; i++)
	{
		if(f)
			sprintf(p, "%s/%d.wav", f, i);
		else
			sprintf(p, "%d.wav", i);
		//printfs(p);
		sounds[clone3d_Colt_Walker + i - 1].chunk = SDLK_LoadSound(p);
	}
	if(f)
		sprintf(p, "%s/%d.wav", f, 3);
	else
		sprintf(p, "%d.wav", 3);
	//printfs(p);
	free(p);

	Mix_AllocateChannels(count);
	ws_init = 1;
	return 1;
}

void Sound_FreeGameSound(void)
{
	if(!ws_init)
		return;
	int count = 0;
	int i;
	for(i = 0; i < total_sound_source_type; i++)
		count += Channel_Count[i];
	for(i = 0; i < count; i++)
	{
		if(sounds[i].chunk)
		{
			SDLK_FreeSound(sounds[i].channel, sounds[i].chunk);
		}
	}
	Mix_AllocateChannels(0);
	free(sounds);
	sounds = NULL;
	ws_init = 0;
}

void Sound_PlayGameSound(const sound_effect *e)
{
	if(!ws_init)
		return;
	if(!e)
		return;
	int channel = Sound_GetSoundChannel(e);

	if(channel != -2)
	{
		Mix_HaltChannel(sounds[channel].channel);
		Mix_Volume(sounds[channel].channel, e->volumn);
		SDLK_PlaySound(sounds[channel].channel, sounds[channel].chunk);
		/*
			 if(SDLK_SoundIsPlaying(sounds[channel].channel))
			 SDLK_ResumeSound(sounds[channel].channel);
			 else
			 SDLK_PlaySound(sounds[channel].channel, sounds[channel].chunk);
			 */
	}
}

void Sound_PauseGameSound(sound_effect *e)
{
	if(!ws_init)
		return;
	if(!e)
		return;
	int channel = Sound_GetSoundChannel(e);
	if(channel != -2)
		SDLK_PauseSound(sounds[channel].channel);
}

int Sound_GetSoundChannel(const sound_effect *s)
{
	if(!s)
		return -2;
	if(s->type >= total_sound_source_type)
		return -2;
	if(s->source < 0 || s->source >= Channel_Count[s->type])
		return -2;
	int r = 0;
	int i;
	for(i = 0; i < (int)s->type; i++)
		r += Channel_Count[i];
	return(r + s->source);
}

sound_effect * Sound_MakeWeaponFireSound(sound_effect *s, weapon *w, float dis, float range)
{
	if(!s || !w)
		return NULL;
	if(dis > range || range == 0)
		return NULL;

	RETURN_PTR(e, s, sound_effect)

		COPY_VERTEX3(s->position, w->position)
		e->type = gun_fire_sound_type;
	e->source = (weapon_sound_type)w->weapon_index;
	e->volumn = (int)ceil((float)(MIX_MAX_VOLUME) * (1.0 - dis / range));
	return e;
}

void Sound_ContinueGameSound(const sound_effect *e)
{
	if(!ws_init)
		return;
	if(!e)
		return;
	int channel = Sound_GetSoundChannel(e);

	if(channel != -2)
	{
		Mix_Volume(sounds[channel].channel, e->volumn);
		SDLK_PlaySound(sounds[channel].channel, sounds[channel].chunk);
	}
}

