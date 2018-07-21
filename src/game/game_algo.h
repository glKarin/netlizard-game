#ifndef KARIN_GAME_ALGO_H
#define KARIN_GAME_ALGO_H

typedef enum _character_health_type
{
	// god is less than 0
	health_death_type = 0,
	health_danger_type = 20,
	health_fine_type = 60,
	health_full_type = 100,
	health_zombie_type = 250,
	health_zombie_parent_type = 6000
} character_health_type;

typedef enum _character_status_type
{
	idle_status_type = 0,
	run_status_type,
	attack_status_type,
	fighting_status_type,
	reload_status_type,
	runreload_status_type,
	death_status_type,
	other_status_type
} character_status_type;

typedef enum _animation_loop_type
{
	no_loop_type = 0,
	one_type_loop_type,
	one_animation_loop_type
} animation_loop_type;

typedef enum _animation_orientation_type
{
	forward_play_type = 0,
	backward_play_type
} animation_orientation_type;

extern const char *Character_Status_Name[other_status_type];

int Game_GetStatusPriority(character_status_type status);
animation_loop_type Game_GetStatusAniamtionLoop(character_status_type status);
unsigned Game_ChangeStatus(unsigned olds, unsigned news);

#endif
