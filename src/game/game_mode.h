#ifndef KARIN_GAME_MODE_H
#define KARIN_GAME_MODE_H

#include "nl_gl.h"
#include "game/character.h"
#include "nl_game.h"
#include "game_event.h"
#include "game_util.h"
#include "template/list_template.h"

typedef enum _game_state_type
{
	ready_game_type = 0,
	running_game_type,
	pause_game_type,
	finish_game_type
} game_state_type;

typedef enum _game_mode_type
{
	general_game_type = 0,
	death_game_type,
	team_death_game_type,
	bio_game_mode,
} game_mode_type;

typedef enum _game_mode_win_type
{
	win_no_type = 0,
	win_point_type,
	win_time_type,
	win_ace_type
} game_mode_win_type;

typedef enum _game_mode_relive_type
{
	norelive_after_death_type = 0,
	relive_random_place_type,
	relive_constant_place_type,
	relive_from_death_place_type
} game_mode_relive_type;

typedef struct _death_game_mode
{
	game_mode_type mode;
	game_state_type state;
	person_mode p_mode;

	game_mode_win_type win_type;
	game_mode_win_type finish_reason;
	long long start_time;
	long long time;
	long long time_limit;
	int point_target;
	int level;
	int *relive_scene;

	game_mode_relive_type relive_type;
	int relive_time;

	int group_count; // 队伍数量
	int *group_id; // 队伍ID数组
	int *group_person_count; // 队伍人数数组
	int *group_point; // 队伍得分
	game_character ***group_character; // 队伍成员

	int max_point;
	long long game_time;
	long long interval_time;

	game_character *characters;
	int character_count;
	int current_character;

	GL_NETLizard_3D_Model *map;
	Game_Map_Event *event;

	list_template particle_list;
	list_template bullet_list;
	list_template sound_list;
} death_game_mode;

death_game_mode * new_death_game_mode(death_game_mode *mode, person_mode pm, game_mode_win_type win_type, int s, int point, game_mode_relive_type relive_type, int relive_time, int level);
void Mode_InitDeathGameMode(death_game_mode *m, game_character *characters, int character_count, GL_NETLizard_3D_Model *model, Game_Map_Event *event);
void Mode_DeathGameModeMain(death_game_mode *m, int fps, float delta);
void delete_death_game_mode(death_game_mode *mode);
int Mode_CheckDeathGameMode(const death_game_mode *m);
void Mode_PauseGameMode(death_game_mode *m);
void Mode_ContinueGameMode(death_game_mode *m);
void Mode_ResetGameMode(death_game_mode *m);

#endif
