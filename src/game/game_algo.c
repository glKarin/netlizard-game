#include "game_algo.h"

#include <limits.h>

const char *Character_Status_Name[] = {
	"Idle",
	"Run",
	"Attack",
	"Reload",
	"Death"
};

int Game_GetStatusPriority(character_status_type status)
{
	switch(status)
	{
		case run_status_type:
			return 5;
		case idle_status_type:
			return 6;
		case crouch_status_type:
		case jump_status_type:
		case swim_status_type:
			return 4;
		case attack_status_type:
			return 3;
		case reload_status_type:
			return 2;
		case death_status_type:
			return 1;
		default:
			return INT_MAX;
	}
}

animation_loop_type Game_GetStatusAniamtionLoop(character_status_type status)
{
	switch(status)
	{
		case run_status_type:
		case jump_status_type:
		case walk_status_type:
		case crouch_status_type:
			return one_animation_loop_type;
		case idle_status_type:
			return one_type_loop_type;
		case attack_status_type:
			return one_animation_loop_type;
		case reload_status_type:
			return no_loop_type;
		case death_status_type:
			return no_loop_type;
		default:
			return no_loop_type;
	}
}

unsigned Game_ChangeStatus(unsigned olds, unsigned news)
{
	int priority = Game_GetStatusPriority(olds);
	int priority_new = Game_GetStatusPriority(news);
	if(priority_new <= priority)
		return 1;
	return 0;
}
