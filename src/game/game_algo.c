#include "game_algo.h"

#include <limits.h>

const char *Character_Status_Name[other_status_type] = {
	"Idle",
	"Run",
	"Attack",
	"Fighting",
	"Reload",
	"Run Reload",
	"Death"
};

int Game_GetStatusPriority(character_status_type status)
{
	switch(status)
	{
		case run_status_type:
			return 4;
		case idle_status_type:
			return 4;
		case attack_status_type:
		case fighting_status_type:
			return 3;
		case runreload_status_type:
			return 2;
		case reload_status_type:
			return 1;
		case death_status_type:
			return 0;
		default:
			return INT_MAX;
	}
}

animation_loop_type Game_GetStatusAniamtionLoop(character_status_type status)
{
	switch(status)
	{
		case run_status_type:
			return one_animation_loop_type;
		case idle_status_type:
			return one_type_loop_type;
		case attack_status_type:
		case fighting_status_type:
			return one_animation_loop_type;
		case reload_status_type:
		case runreload_status_type:
			return no_loop_type;
		case death_status_type:
			return no_loop_type;
		default:
			return no_loop_type;
	}
}

