#ifndef KARIN_GAME_SOUND_H
#define KARIN_GAME_SOUND_H

#include "weapon.h"

typedef enum _sound_source_type
{
	gun_fire_sound_type = 0,
	character_dead_sound_type,
	bullet_wall_sound_type,
	bullet_cross_sound_type,
	bullet_character_sound_type,
	character_move_sound_type,
	total_sound_source_type
} sound_source_type;

typedef struct _sound_effect
{
	sound_source_type type;
	int source;
	float position[3];
	int volumn;
} sound_effect;

int Sound_LoadGameSound(void);
void Sound_PlayGameSound(const sound_effect *e);
void Sound_PauseGameSound(sound_effect *e);
void Sound_FreeGameSound(void);
int Sound_GetSoundChannel(const sound_effect *s);
sound_effect * Sound_MakeWeaponFireSound(sound_effect *s, weapon *w, float dis, float range);
void Sound_ContinueGameSound(const sound_effect *e);

#endif
