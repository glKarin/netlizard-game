#ifndef KARIN_GAME_ALGO_H
#define KARIN_GAME_ALGO_H

typedef enum _character_part_type
{
	character_leg_part_type = 0,
	character_body_part_type,
	character_all_part_type,
} character_part_type;

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
	// all
	idle_status_type = 1,
	death_status_type = 1 << 1,

	// leg
	run_status_type = 1 << 8,
	jump_status_type = 1 << 9,
	crouch_status_type = 1 << 10,
	walk_status_type = 1 << 11,
	swim_status_type = 1 << 12,

	//body
	reload_status_type = 1 << 16,
	attack_status_type = 1 << 17,

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

extern const char *Character_Status_Name[];

int Game_GetStatusPriority(character_status_type status);
animation_loop_type Game_GetStatusAniamtionLoop(character_status_type status);
unsigned Game_ChangeStatus(unsigned olds, unsigned news);

#endif
