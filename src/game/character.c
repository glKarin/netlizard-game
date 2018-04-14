#include "character.h"
#include "nl_std.h"
#include "netlizard/netlizard.h"

#include "opengl.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define JUMP_SPEED 230.0
#define MOVE_UNIT 800.0
#define TURN_UNIT 150.0

typedef struct _game_model_resource
{
	int type;
	char *mesh_file;
	char *tex_file;
	char *anim_file;
	float scale;
	weapon_attack_type attack_type;
	float width;
	float height;
	float full_height;
	float move_unit;
	float turn_unit;
	float jump_speed;
} game_model_resource;

static const game_model_resource Game_Model_Resource[lol_total_model] = {
	{egypt3d_worm, _KARIN_GAME_DIR"egypt3d/un1.png", "1", NULL, NETLIZARD_CHARACTER_SCALE, short_attack_type, 80, 65, 105, 550, 120, 250},
	{egypt3d_scorpion, _KARIN_GAME_DIR"egypt3d/un6.png", "6", NULL, NETLIZARD_CHARACTER_SCALE, long_attack_type, 70, 185, 230, 500, 60, 80},
	{egypt3d_fly_fish, _KARIN_GAME_DIR"egypt3d/un4.png", "4", NULL, NETLIZARD_CHARACTER_SCALE, short_attack_type, 50, 45, 160, 600, 120, 100},
	{egypt3d_anubis, _KARIN_GAME_DIR"egypt3d/un5.png", "5", NULL, NETLIZARD_CHARACTER_SCALE, short_attack_type, 60, 180, 270, 580, 120, 200},
	{egypt3d_tentacle, _KARIN_GAME_DIR"egypt3d/un7.png", "7", NULL, NETLIZARD_CHARACTER_SCALE, short_attack_type, 90, 160, 780, 400, 120, 50},
	{egypt3d_machine_monster, _KARIN_GAME_DIR"egypt3d/un2.png", "2", NULL, NETLIZARD_CHARACTER_SCALE, long_attack_type, 80, 150, 270, 500, 60, 30},
	{egypt3d_fly_machine, _KARIN_GAME_DIR"egypt3d/un3.png", "3", NULL, NETLIZARD_CHARACTER_SCALE, long_attack_type, 100, 40, 140, 550, 60, 150},

	{clone3d_human_cloning, _KARIN_GAME_DIR"clone3d/un1.png", "1", NULL, NETLIZARD_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{clone3d_soldier, _KARIN_GAME_DIR"clone3d/un1.png", "3", NULL, NETLIZARD_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{clone3d_human_cloning_old, _KARIN_GAME_DIR"clone3d/un1.png", "2", NULL, NETLIZARD_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{clone3d_soldier2, _KARIN_GAME_DIR"clone3d/un1.png", "4", NULL, NETLIZARD_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{clone3d_bio_soldier, _KARIN_GAME_DIR"clone3d/un2.png", "2", NULL, NETLIZARD_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{clone3d_machine, _KARIN_GAME_DIR"clone3d/un3.png", "3", NULL, NETLIZARD_CHARACTER_SCALE, long_attack_type, 180, 280, 410, MOVE_UNIT, TURN_UNIT, 40},

	{caitlyn_original, CAITLYN_ORIGINAL_MESH, CAITLYN_ORIGINAL_PNG, CAITLYN_ORIGINAL_ANIM, CAITLYN_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{jinx_original, JINX_ORIGINAL_MESH, JINX_ORIGINAL_PNG, JINX_ORIGINAL_ANIM, JINX_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED}
};

const char *Character_Model_Name[lol_total_model] = {
	"Egypt Worm",
	"Egypt Scorpion",
	"Egypt Fly Fish",
	"Egypt Anubis",
	"Egypt Tentacle",
	"Egypt Machine Monster",
	"Egypt Fly Machine",
	"Cloning Human",
	"Soldier",
	"Old Cloning Human",
	"Black soldier",
	"Bio Soldier",
	"Machine",
	//"Damage_Machine",

	"Caitlyn",
	"Jinx"
	/*
	"Caitlyn Safari",
	"Caitlyn Arctic Warfare",
	"Caitlyn Officer"
		*/
};

int Game_ComputeAnimationPlayFrameCount(model_source_type source, character_animation_data *animation, int fps, long long time)
{
	//if(!model || !model -> anim)
	if(!animation)
		return -1;
	if(source == unavailable_model_type)
		return -1;
	int f = 0;
	if(fps >= 0)
	{
		int anim_fps = animation -> fps;
		float nap = (float)anim_fps * (float)fps / 30.0;
		if(nap > 0.0)
		{
			float t = 1000.0 / nap;
			if((float)(time - animation -> last_play_time) > t)
			{
				float p = (float)(time - animation -> last_play_time) / t;
				double nf = 0.0;
				double nl = modf(p, &nf);
				f = (int)nf;
				long long tl = (long long)(t * nl);
				animation -> last_play_time = time - tl;
			}
			else
				f = 0; // 8 25
		}
		else
			f = 0; // 2017 8 25
	}
	else
		f = 1;
	return f;
}

// -1 no next frame
// -2 need next animation
// -3 data is null or other invalid
int Game_GetAnimationNextFrame(const character_animation_data *data, int f)
{
	if(!data)
		return -3;
	if(f <= 0)
		return -3;
	if(data -> anim_orient == forward_play_type)
	{
		if(data -> anim_loop == no_loop_type)
		{
			if(data -> frame == data -> frame_count - 1)
			{
				return -1;
			}
			else if(data -> frame + f >= data -> frame_count - 1)
			{
				return data -> frame_count - 1;
			}
			else
			{
				return data -> frame + f;
			}
		}
		else if(data -> anim_loop == one_animation_loop_type)
		{
			return (data -> frame + f) % data -> frame_count;
		}
		else if(data -> anim_loop == one_type_loop_type)
		{
			if(data -> frame == data -> frame_count - 1)
			{
				return -2;
			}
			else if(data -> frame + f >= data -> frame_count - 1)
			{
				return data -> frame_count - 1;
			}
			else
			{
				return data -> frame + f;
			}
		}
	}
	else
	{
		if(data -> anim_loop == no_loop_type)
		{
			if(data -> frame == 0)
			{
				return -1;
			}
			else if(data -> frame - f <= 0)
			{
				return 0;
			}
			else
			{
				return data -> frame - f;
			}
		}
		else if(data -> anim_loop == one_animation_loop_type)
		{
			int p = data -> frame - f;
			if(p > 0)
				return p % data -> frame_count;
			else if(p < 0)
				return data -> frame_count - KARIN_ABS(p % data -> frame_count);
			else
				return p;
		}
		else if(data -> anim_loop == one_type_loop_type)
		{
			if(data -> frame == 0)
			{
				return -2;
			}
			else if(data -> frame - f <= 0)
			{
				return 0;
			}
			else
			{
				return data -> frame - f;
			}
		}
	}
	return -3;
}

int Game_GetNETLizardAnimationIndex(GL_NETLizard_3D_Animation_Model *model, NETLizard_3D_Animation_Type type)
{
	if(!model || type == Animation_Unknow_Type)
		return -1;
	unsigned int i;
	for(i = 0; i < model -> anim_count; i++)
	{
		if(model -> animations[i].type == type)
			return i;
	}
	return -1;
}

int Game_UpdateCharacterStatus(game_character *gamer, character_status_type status)
{
	if(!gamer)
		return 0;
	if(gamer -> model.source == lol_model_type)
	{
		if(!gamer -> model.lol_character.model -> anim)
			return 0;

		int anim = -1;
		int frame_count = -1;
		if(status == death_status_type)
		{
			anim = gamer -> model.lol_character.anim_list[LOL_Death_Type];
		}
		else if(status == reload_status_type || status == runreload_status_type)
		{
			anim = gamer -> model.lol_character.anim_list[LOL_Idle3_Type];
			frame_count = 83; // idle 3 160 / 340
		}
		else if(status == run_status_type)
		{
			if(gamer -> current_weapon.type == shot_gun_type || gamer -> current_weapon.type == mini_submachine_gun_type || gamer -> current_weapon.type ==  automatic_rifle_type || gamer -> current_weapon.type == sniper_rifle_type || gamer -> current_weapon.type == machine_gun_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Run1_Type];
			else if(gamer -> current_weapon.type == launcher1_gun_type || gamer -> current_weapon.type == launcher2_gun_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Run2_Type];
			else if(gamer -> current_weapon.type == pistol_gun_type || gamer -> current_weapon.type == dagger_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Run3_Type];
			else if(gamer -> current_weapon.type ==  grenades_type || gamer -> current_weapon.type == flash_flares_type || gamer -> current_weapon.type == smoke_bomb_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Run4_Type];
			else
				anim = gamer -> model.lol_character.anim_list[LOL_Run1_Type];
		}
		else if(status == attack_status_type)
		{
			if(gamer -> current_weapon.type == shot_gun_type || gamer -> current_weapon.type == mini_submachine_gun_type || gamer -> current_weapon.type ==  automatic_rifle_type || gamer -> current_weapon.type == sniper_rifle_type || gamer -> current_weapon.type == machine_gun_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Attack1_Type];
			else if(gamer -> current_weapon.type == launcher1_gun_type || gamer -> current_weapon.type == launcher2_gun_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Attack2_Type];
			else if(gamer -> current_weapon.type == pistol_gun_type || gamer -> current_weapon.type == dagger_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Attack3_Type];
			else if(gamer -> current_weapon.type ==  grenades_type || gamer -> current_weapon.type == flash_flares_type || gamer -> current_weapon.type == smoke_bomb_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Attack4_Type];
			else
				anim = gamer -> model.lol_character.anim_list[LOL_Attack1_Type];
		}
		else if(status == fighting_status_type)
		{
			if(gamer -> current_weapon.type == shot_gun_type || gamer -> current_weapon.type == mini_submachine_gun_type || gamer -> current_weapon.type ==  automatic_rifle_type || gamer -> current_weapon.type == sniper_rifle_type || gamer -> current_weapon.type == machine_gun_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Attack1_Type];
			else if(gamer -> current_weapon.type == launcher1_gun_type || gamer -> current_weapon.type == launcher2_gun_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Attack2_Type];
			else if(gamer -> current_weapon.type == pistol_gun_type || gamer -> current_weapon.type == dagger_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Attack3_Type];
			else if(gamer -> current_weapon.type ==  grenades_type || gamer -> current_weapon.type == flash_flares_type || gamer -> current_weapon.type == smoke_bomb_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Attack4_Type];
			else
				anim = gamer -> model.lol_character.anim_list[LOL_Attack1_Type];
		}
		else
		{
			if(gamer -> current_weapon.type == shot_gun_type || gamer -> current_weapon.type == mini_submachine_gun_type || gamer -> current_weapon.type ==  automatic_rifle_type || gamer -> current_weapon.type == sniper_rifle_type || gamer -> current_weapon.type == machine_gun_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Idle1_Type];
			else if(gamer -> current_weapon.type == launcher1_gun_type || gamer -> current_weapon.type == launcher2_gun_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Idle2_Type];
			else if(gamer -> current_weapon.type == pistol_gun_type || gamer -> current_weapon.type == dagger_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Idle3_Type];
			else if(gamer -> current_weapon.type ==  grenades_type || gamer -> current_weapon.type == flash_flares_type || gamer -> current_weapon.type == smoke_bomb_type)   
				anim = gamer -> model.lol_character.anim_list[LOL_Idle4_Type];
			else
				anim = gamer -> model.lol_character.anim_list[LOL_Idle1_Type];
		}
		if(anim != -1)
		{
			gamer -> animation.frame = 0;
			gamer -> animation.anim = anim;
			gamer -> animation.frame_count = frame_count == -1 ? (int)gamer -> model.lol_character.model -> anim -> animation[gamer -> animation.anim].animation_bone[0].frame_count : frame_count;
			gamer -> animation.anim_loop = Game_GetStatusAniamtionLoop(status);
			gamer -> animation.fps = gamer -> model.lol_character.model -> anim -> animation[anim].fps;
		}
		else
			return 0;
	}
	else if(gamer -> model.source == netlizard_model_type)
	{
		if(!gamer -> model.netlizard_character.model)
			return 0;

		int anim = -1;
		if(status == death_status_type)
		{
			int a1 = Game_GetNETLizardAnimationIndex(gamer -> model.netlizard_character.model, Animation_Dead1_Type);
			int a2 = Game_GetNETLizardAnimationIndex(gamer -> model.netlizard_character.model, Animation_Dead2_Type);
			if(a1 != -1 && a2 != -1)
				anim = rand() % 2 == 0 ? a1 : a2;
			else if(a1 != -1)
				anim = a1;
			else if(a2 != -1)
				anim = a2;
			else
				anim = -1;
		}
		else if(status == run_status_type)
		{
			anim = Game_GetNETLizardAnimationIndex(gamer -> model.netlizard_character.model, Animation_Run_Type);
		}
		else if(status == attack_status_type || status == reload_status_type)
		{
			int a1 = Game_GetNETLizardAnimationIndex(gamer -> model.netlizard_character.model, Animation_Attack1_Type);
			int a2 = Game_GetNETLizardAnimationIndex(gamer -> model.netlizard_character.model, Animation_Attack2_Type);
			if(gamer -> current_weapon.type == pistol_gun_type || gamer -> current_weapon.type == dagger_type || gamer -> current_weapon.type ==  grenades_type || gamer -> current_weapon.type == flash_flares_type || gamer -> current_weapon.type == smoke_bomb_type)   
				anim = a1;
			else if(gamer -> current_weapon.type == shot_gun_type || gamer -> current_weapon.type == mini_submachine_gun_type || gamer -> current_weapon.type ==  automatic_rifle_type || gamer -> current_weapon.type == sniper_rifle_type || gamer -> current_weapon.type == machine_gun_type || gamer -> current_weapon.type == launcher1_gun_type || gamer -> current_weapon.type == launcher2_gun_type)   
				anim = a2;
			else
			{
				if(a1 != -1 && a2 != -1)
					anim = rand() % 2 == 0 ? a1 : a2;
				else if(a1 != -1)
					anim = a1;
				else if(a2 != -1)
					anim = a2;
				else
					anim = -1;
			}
		}
		else if(status == fighting_status_type || status == runreload_status_type)
		{
			int a1 = Game_GetNETLizardAnimationIndex(gamer -> model.netlizard_character.model, Animation_Fighting1_Type);
			int a2 = Game_GetNETLizardAnimationIndex(gamer -> model.netlizard_character.model, Animation_Fighting2_Type);
			if(gamer -> current_weapon.type == pistol_gun_type || gamer -> current_weapon.type == dagger_type || gamer -> current_weapon.type ==  grenades_type || gamer -> current_weapon.type == flash_flares_type || gamer -> current_weapon.type == smoke_bomb_type)   
				anim = a1;
			else if(gamer -> current_weapon.type == shot_gun_type || gamer -> current_weapon.type == mini_submachine_gun_type || gamer -> current_weapon.type ==  automatic_rifle_type || gamer -> current_weapon.type == sniper_rifle_type || gamer -> current_weapon.type == machine_gun_type || gamer -> current_weapon.type == launcher1_gun_type || gamer -> current_weapon.type == launcher2_gun_type)   
				anim = a2;
			else
			{
				if(a1 != -1 && a2 != -1)
					anim = rand() % 2 == 0 ? a1 : a2;
				else if(a1 != -1)
					anim = a1;
				else if(a2 != -1)
					anim = a2;
				else
				{
					a1 = Game_GetNETLizardAnimationIndex(gamer -> model.netlizard_character.model, Animation_Attack1_Type);
					a2 = Game_GetNETLizardAnimationIndex(gamer -> model.netlizard_character.model, Animation_Attack2_Type);
					if(gamer -> current_weapon.type == pistol_gun_type || gamer -> current_weapon.type == dagger_type || gamer -> current_weapon.type ==  grenades_type || gamer -> current_weapon.type == flash_flares_type || gamer -> current_weapon.type == smoke_bomb_type)   
						anim = a1;
					else if(gamer -> current_weapon.type == shot_gun_type || gamer -> current_weapon.type == mini_submachine_gun_type || gamer -> current_weapon.type ==  automatic_rifle_type || gamer -> current_weapon.type == sniper_rifle_type || gamer -> current_weapon.type == machine_gun_type || gamer -> current_weapon.type == launcher1_gun_type || gamer -> current_weapon.type == launcher2_gun_type)   
						anim = a2;
					else
					{
						if(a1 != -1 && a2 != -1)
							anim = rand() % 2 == 0 ? a1 : a2;
						else if(a1 != -1)
							anim = a1;
						else if(a2 != -1)
							anim = a2;
						else
							anim = -1;
					}
				}
			}
		}
		else
		{
			anim = Game_GetNETLizardAnimationIndex(gamer -> model.netlizard_character.model, Animation_Idle_Type);
		}
		if(anim != -1)
		{
			gamer -> animation.frame = 0;
			gamer -> animation.anim = anim;
			gamer -> animation.frame_count = gamer -> model.netlizard_character.model -> animations[gamer -> animation.anim].end - gamer -> model.netlizard_character.model -> animations[gamer -> animation.anim].begin + 1;
			gamer -> animation.anim_loop = Game_GetStatusAniamtionLoop(status);
			gamer -> animation.fps = NETLIZARD_ANIMATION_FPS;
		}
		else
			return 0;
	}
	else
		return 0;
	gamer -> status = status;
	return 1;
}

game_character * new_lol_game_character(game_character *c, const char *meshf, const char *ddsf[], int count, const char *animf, float x, float y, float z, float xr, float yr, float f, float w, float h, float th, float mu, float tu, float speed, int scene)
{
	if(!meshf || !animf)
		return NULL;
	RETURN_PTR(gamer, c, game_character)	

		gamer -> position[0] = x;
	gamer -> position[1] = y;
	gamer -> position[2] = z;
	gamer -> x_angle = xr;
	gamer -> y_angle = yr;
	gamer -> health = health_full_type;
	gamer -> health_full = gamer -> health;
	gamer -> width = w;
	gamer -> height = h;
	gamer -> full_height = th;
	gamer -> move_unit = mu;
	gamer -> turn_unit = tu;
	gamer -> z_jump_speed = speed;
	gamer -> z_moving.state = no_z_type;
	gamer -> z_moving.jump_speed = 0.0;
	gamer -> z_moving.speed = 0.0;
	gamer -> z_moving.start_time = 0;
	gamer -> z_moving.start_z = 0;
	gamer -> scene = scene;
	gamer -> scene_collision_result = scene == -1 ? 0 : 2;
	gamer -> collision_item = -1;
	gamer -> score.kill = 0;
	gamer -> score.death = 0;
	gamer -> score.assist = 0;
	gamer -> score.killed_character = -1;
	gamer -> score.kill_character = -1;
	gamer -> group = 0;
	gamer -> index = 0;

	LOL_Model *model = new_LOL_Model(meshf, animf, ddsf, count);
	if(!model)
	{
		gamer -> model.source = unavailable_model_type;
	}
	else
	{
		gamer -> model.lol_character.source = lol_model_type;
		gamer -> model.lol_character.model = model;
		gamer -> model.lol_character.scale= f;
		gamer -> model.lol_character.x_offset = 90.0;
		int i;
		for(i = 0; i < LOL_Total_Type; i++)
		{
			if(model -> anim)
			{
				LOL_GetAnimationRangeByType(model, i, gamer -> model.lol_character.anim_list + i, NULL);
				//printfs(s);
			}
			else
				gamer -> model.lol_character.anim_list[i] = -1;
		}
	}

	new_weapon(&gamer -> current_weapon, clone3d_M16);
	gamer -> current_weapon.position[0] = gamer -> position[0];
	gamer -> current_weapon.position[1] = gamer -> position[1];
	gamer -> current_weapon.position[2] = gamer -> position[2] + gamer -> height;
	gamer -> current_weapon.x_angle = gamer -> x_angle;
	gamer -> current_weapon.y_angle = gamer -> y_angle;

	Game_UpdateCharacterStatus(gamer, idle_status_type);
	AI_MakeComputeAction(&gamer -> ai, 0, aiaction_idle_type);
	return gamer;
}

void Game_RenderGameCharacter(const game_character *gamer)
{
	if(!gamer)
		return;
	if(gamer -> model.source == lol_model_type)
	{
		if(!gamer -> model.lol_character.model)
			return;
		glPushMatrix();
		{
			glTranslatef(gamer -> position[0], gamer -> position[1], gamer -> position[2]);
			glRotatef(gamer -> model.lol_character.x_offset, 1.0, 0.0, 0.0);
			glRotatef(gamer -> y_angle, 0.0f, 1.0f, 0.0f);

			if(gamer -> model.lol_character.scale != 1.0)
				glScalef(gamer -> model.lol_character.scale, gamer -> model.lol_character.scale, gamer -> model.lol_character.scale);
			LOL_RenderModel(gamer -> model.lol_character.model, 1, gamer -> animation.anim, gamer -> animation.frame);
			//GLfloat yr = Algo_FormatAngle(-gamer -> y_angle - 180.0);
			//glRotatef(90.0, 1.0, 0.0, 0.0);
			//glRotatef(yr, 0.0f, 1.0f, 0.0f);
		}
		glPopMatrix();
	}

	else if(gamer -> model.source == netlizard_model_type)
	{
		if(!gamer -> model.netlizard_character.model)
			return;
		if(gamer -> current_weapon.model && gamer -> current_weapon.model -> tp_model)
		{
			glPushMatrix();
			{
				if(gamer -> status == attack_status_type || gamer -> status == fighting_status_type)
				{
					glTranslatef(gamer -> current_weapon.position[0], gamer -> current_weapon.position[1], gamer -> current_weapon.position[2]);
					glRotatef(gamer -> y_angle, 0.0f, 0.0f, 1.0f);
					glTranslatef(0.0, gamer -> width, 0.0);
					glTranslatef(gamer -> current_weapon.model -> position[0], gamer -> current_weapon.model -> position[1], gamer -> current_weapon.model -> position[2]);
					if(gamer -> current_weapon.type == pistol_gun_type || gamer -> current_weapon.type == dagger_type || gamer -> current_weapon.type ==  grenades_type || gamer -> current_weapon.type == flash_flares_type || gamer -> current_weapon.type == smoke_bomb_type)   
						glTranslatef(0.0, -90.0, 0.0);
				}
				else if(gamer -> status == death_status_type)
				{
					glTranslatef(gamer -> position[0], gamer -> position[1], gamer -> position[2]);
					glRotatef(gamer -> y_angle, 0.0f, 0.0f, 1.0f);
					glTranslatef(gamer -> current_weapon.model -> position[0], gamer -> current_weapon.model -> position[1], gamer -> current_weapon.model -> position[2]);
				}
				else
				{
					if(gamer -> current_weapon.type == pistol_gun_type || gamer -> current_weapon.type == dagger_type || gamer -> current_weapon.type ==  grenades_type || gamer -> current_weapon.type == flash_flares_type || gamer -> current_weapon.type == smoke_bomb_type)   
					{
						glTranslatef(gamer -> position[0], gamer -> position[1], gamer -> position[2] + gamer -> full_height / 2);
						glRotatef(gamer -> y_angle, 0.0f, 0.0f, 1.0f);
						glRotatef(90.0, 1.0f, 0.0f, 0.0f);
						glTranslatef(-30.0, 0.0, 0.0);
						glTranslatef(0.0, 0.0, gamer -> current_weapon.model -> position[2]);
					}
					else if(gamer -> current_weapon.type == shot_gun_type || gamer -> current_weapon.type == mini_submachine_gun_type || gamer -> current_weapon.type ==  automatic_rifle_type || gamer -> current_weapon.type == sniper_rifle_type || gamer -> current_weapon.type == machine_gun_type || gamer -> current_weapon.type == launcher1_gun_type || gamer -> current_weapon.type == launcher2_gun_type)   
					{
						glTranslatef(gamer -> current_weapon.position[0], gamer -> current_weapon.position[1], gamer -> current_weapon.position[2]);
						glRotatef(gamer -> y_angle, 0.0f, 0.0f, 1.0f);
						glTranslatef(0.0, gamer -> width, 0.0);
						glRotatef(90.0, 1.0f, 0.0f, 0.0f);
						glRotatef(90.0, 0.0f, 1.0f, 0.0f);
						glTranslatef(30.0, 0.0, 0.0);
						glTranslatef(0.0, 0.0, gamer -> current_weapon.model -> position[2]);
					}
				}
				glRotatef(gamer -> current_weapon.model -> tp_model -> item_meshes[0].angle[0], 1.0f, 0.0f, 0.0f);
				glRotatef(gamer -> current_weapon.model -> tp_model -> item_meshes[0].angle[1], 0.0f, 0.0f, 1.0f);
				if(gamer -> current_weapon.model -> scale != 1.0)
					glScalef(gamer -> current_weapon.model -> scale, gamer -> current_weapon.model -> scale, gamer -> current_weapon.model -> scale);
				glPushAttrib(GL_POLYGON_BIT);
				{
					oglDisable(GL_CULL_FACE);
					//NETLizard_RenderGL3DModel(gamer -> current_weapon.model.tp_model);
					NETLizard_RenderGL3DMesh(&(gamer -> current_weapon.model -> tp_model -> item_meshes[0].item_mesh), gamer -> current_weapon.model -> tp_model -> texes);
				}
				glPopAttrib();
			}
			glPopMatrix();
		}

		glPushMatrix();
		{
			glTranslatef(gamer -> position[0], gamer -> position[1], gamer -> position[2]);
			//glRotatef(gamer -> x_angle, 1.0f, 0.0f, 0.0f);
			glRotatef(gamer -> y_angle, 0.0f, 0.0f, 1.0f);
			glRotatef(gamer -> model.netlizard_character.z_offset, 0.0f, 0.0f, 1.0f);
			//glRotatef(-90.0, 0.0f, 0.0f, 1.0f);
			if(gamer -> model.netlizard_character.scale != 1.0)
				glScalef(gamer -> model.netlizard_character.scale, gamer -> model.netlizard_character.scale, gamer -> model.netlizard_character.scale);
			NETLizard_RenderGL3DAnimationModel(gamer -> model.netlizard_character.model, gamer -> animation.anim, gamer -> animation.frame);
		}
		glPopMatrix();
	}
	else
		return;
}

void Game_CharacterPlayAnimation(game_character *gamer, long long time, int fps)
{
	if(!gamer)
		return;
	if(gamer -> model.source == unavailable_model_type)
		return;
	int f = Game_ComputeAnimationPlayFrameCount(gamer -> model.source, &gamer -> animation, fps, time);
	character_status_type status;
	animation_orientation_type o = forward_play_type;
	if(gamer -> health == health_death_type)
	{
		gamer -> health = health_death_type;
		status = death_status_type;
	}
	else
	{
		if(gamer -> ai.type != ai_player_type)
			AI_ProcessAction(&gamer -> ai, time);
		ai_action_type a = gamer -> ai.action;
		if(a & aiaction_reload_type && gamer -> current_weapon.status == reload_type && gamer -> model.source == lol_model_type)
		{
			status = reload_status_type;
			if(a & aiaction_movexyz_type || a & aiaction_jump_type || a & aiaction_turny_type)
				status = runreload_status_type;
		}
		else if(a & aiaction_attack_type && !((gamer -> current_weapon.status == outofammo_type || gamer -> current_weapon.status == reload_type) && gamer -> model.source == lol_model_type))
		{
			status = attack_status_type;
			if(a & aiaction_movexyz_type || a & aiaction_jump_type)
				status = fighting_status_type;
		}
		else if(a & aiaction_fight_type)
		{
			status = run_status_type;
			if(gamer -> ai.fighting)
				status = fighting_status_type;
		}
		else if(a & aiaction_movexyz_type || a & aiaction_jump_type || a & aiaction_turny_type)
			status = run_status_type;
		else if(a == aiaction_idle_type || a == aiaction_stand_type)
			status = idle_status_type;
		else
			status = idle_status_type;

		if(status == run_status_type && (a & aiaction_movebackward_type))
			o = backward_play_type;
	}

	if(status == gamer -> status)
	{
		if(gamer -> model.source == lol_model_type)
		{
			if(status == attack_status_type || status == fighting_status_type)
			{
				float anf = (float)f * gamer -> current_weapon.firing_rate;
				f = KARIN_MAX((int)floor(anf), f);
			}
			else if(status == reload_status_type || status == runreload_status_type)
			{
				//float anf = (float)f * (((float)(gamer -> animation.frame_count / (float)fps)) / gamer -> current_weapon.reload_time);
				float anf = (float)f * ((float)(gamer -> animation.frame_count / gamer -> current_weapon.reload_time) / (float)fps);
				f = KARIN_MAX((int)floor(anf), f);
			}
		}
		int n = Game_GetAnimationNextFrame(&gamer -> animation, f);
		if(n == -2)
		{
			Game_UpdateCharacterStatus(gamer, status);
			gamer -> animation.last_play_time = time;
		}
		else if(n >= 0)
		{
			gamer -> animation.frame = n;
		}
		else
		{
		}
	}
	else
	{
		int priority = Game_GetStatusPriority(gamer -> status);
		int priority_new = Game_GetStatusPriority(status);
		if((priority >= priority_new) || gamer -> animation.frame == gamer -> animation.frame_count - 1)
		{
			Game_UpdateCharacterStatus(gamer, status);
			gamer -> animation.last_play_time = time;
		}
		else if(gamer -> animation.frame + f > gamer -> animation.frame_count - 1)
		{
			gamer -> animation.frame = gamer -> animation.frame_count - 1;
		}
		else
		{
			if(f > 0)
				gamer -> animation.frame += f;
		}
	}
}

game_character * new_netlizard_game_character(game_character *c, const char *game, const char *file, int index, float x, float y, float z, float xr, float yr, float f, float w, float h, float th, float mu, float tu, float speed, int scene)
{
	if(!file || index < 0 || !game)
		return NULL;

	RETURN_PTR(gamer, c, game_character)	

		gamer -> position[0] = x;
	gamer -> position[1] = y;
	gamer -> position[2] = z;
	gamer -> x_angle = xr;
	gamer -> y_angle = yr;
	gamer -> health = health_full_type;
	gamer -> health_full = gamer -> health;
	gamer -> width = w;
	gamer -> height = h;
	gamer -> full_height = th;
	gamer -> move_unit = mu;
	gamer -> turn_unit = tu;
	gamer -> z_jump_speed = speed;
	gamer -> z_moving.state = no_z_type;
	gamer -> z_moving.jump_speed = 0.0;
	gamer -> z_moving.speed = 0.0;
	gamer -> z_moving.start_z = 0;
	gamer -> z_moving.start_time = 0;
	gamer -> scene = scene;
	gamer -> scene_collision_result = scene == -1 ? 0 : 2;
	gamer -> collision_item = -1;
	gamer -> score.kill = 0;
	gamer -> score.death = 0;
	gamer -> score.assist = 0;
	gamer -> group = 0;
	gamer -> index = 0;

	GL_NETLizard_3D_Animation_Model *model = NULL;
	if(strcasecmp(game, "egypt3d") == 0)
		model = NETLizard_ReadGLEgypt3DRoleModelFile(file, index);
	else if(strcasecmp(game, "clone3d") == 0)
		model = NETLizard_ReadGLClone3DRoleModelFile(file, index);
	else
		gamer -> model.source = unavailable_model_type;

	if(!model)
	{
		gamer -> model.source = unavailable_model_type;
	}
	else
	{
		gamer -> model.netlizard_character.source = netlizard_model_type;
		gamer -> model.netlizard_character.model = model;
		gamer -> model.netlizard_character.scale= f;
		gamer -> model.netlizard_character.z_offset = 90.0;
	}

	new_weapon(&gamer -> current_weapon, clone3d_M16);
	gamer -> current_weapon.position[0] = gamer -> position[0];
	gamer -> current_weapon.position[1] = gamer -> position[1];
	gamer -> current_weapon.position[2] = gamer -> position[2] + gamer -> height;
	gamer -> current_weapon.x_angle = gamer -> x_angle;
	gamer -> current_weapon.y_angle = gamer -> y_angle;

	Game_UpdateCharacterStatus(gamer, idle_status_type);
	AI_MakeComputeAction(&gamer -> ai, 0, aiaction_idle_type);
	return gamer;
}

void delete_game_character(game_character *gamer)
{
	if(!gamer)
		return;
	FREE_PTR(gamer -> name);
	delete_game_ai(&gamer -> ai);
	delete_weapon(&gamer -> current_weapon);
	Game_FreeCharacterModel(&gamer -> model);
}

void Game_UpdateCharacterPositionAndDirection(game_character *gamer, float x, float y, float z, float xr, float yr)
{
	if(!gamer)
		return;
	gamer -> position[0] = x;
	gamer -> position[1] = y;
	gamer -> position[2] = z;
	gamer -> x_angle = xr;
	gamer -> y_angle = yr;
}

game_character * new_game_character(game_character *c, int type, float x, float y, float z, float xr, float yr, int id, const char *name, int scene, weapon_model_type wt)
{
	RETURN_PTR(gamer, c, game_character)

		const game_model_resource *r = Game_Model_Resource + type;
	if(type >= egypt3d_worm && type <= egypt3d_fly_machine)
	{
		new_netlizard_game_character(gamer, "egypt3d", r -> mesh_file, atoi(r -> tex_file), x, y, z, xr, yr, r -> scale, r -> width, r -> height, r -> full_height, r -> move_unit, r -> turn_unit, r -> jump_speed, scene);
		new_weapon(&gamer -> current_weapon, egypt3d_Worm_Weapon + egypt3d_worm);
	}
	else if(type >= clone3d_human_cloning && type <= clone3d_soldier2)
	{
		new_netlizard_game_character(gamer, "clone3d", r -> mesh_file, 1, x, y, z, xr, yr, r -> scale, r -> width, r -> height, r -> full_height, r -> move_unit, r -> turn_unit, r -> jump_speed, scene);
		if(type != clone3d_human_cloning)
		{
			GL_NETLizard_3D_Animation_Model *model = gamer -> model.netlizard_character.model;
			if(glIsTexture(model -> tex -> texid))
			{
				glDeleteTextures(1, &model -> tex -> texid);
			}
			free(model -> tex);
			char *name = NEW_II(char, strlen(_KARIN_GAME_DIR) + 1 + 17 + 1);
			sprintf(name, "%s/clone3d/w/w%s.png", _KARIN_GAME_DIR, r -> tex_file);
			model -> tex = new_texture_from_nl_v3_3d_file(name);
			free(name);
		}
		if(wt < egypt3d_Worm_Weapon)
			new_weapon(&gamer -> current_weapon, wt);
		else
			new_weapon(&gamer -> current_weapon, clone3d_M16);
	}
	else if(type >= clone3d_bio_soldier && type <= clone3d_machine)
	{
		new_netlizard_game_character(gamer, "clone3d", r -> mesh_file, atoi(r -> tex_file), x, y, z, xr, yr, r -> scale, r -> width, r -> height, r -> full_height, r -> move_unit, r -> turn_unit, r -> jump_speed, scene);
		if(type == clone3d_machine)
			new_weapon(&gamer -> current_weapon, clone3d_Machine_Weapon);
		else
		{
			if(wt < egypt3d_Worm_Weapon)
				new_weapon(&gamer -> current_weapon, wt);
			else
				new_weapon(&gamer -> current_weapon, clone3d_M16);
		}
	}
	else
	{
		const char *dds[1] = {r -> tex_file};
		new_lol_game_character(gamer, r -> mesh_file, dds, 1, r -> anim_file, x, y, z, xr, yr, r -> scale, r -> width, r -> height, r -> full_height, r -> move_unit, r -> turn_unit, r -> jump_speed, scene);
		new_weapon(&gamer -> current_weapon, clone3d_M16);
	}
	gamer -> index = id;
	if(name)
		gamer -> name = strdup(name);
	else
	{
		char *in = itostr(gamer -> index);
		gamer -> name = NEW_II(char, strlen(in) + strlen("Character") + 2);
		sprintf(gamer -> name, "Character-%s", in);
	}
	return gamer;
}

int Game_MakeGameCharacterModel(game_character_model *game_model, unsigned int type)
{
	if(!game_model)
		return 0;
	const game_model_resource *r = Game_Model_Resource + type;
	if(type <= clone3d_machine)
	{
		GL_NETLizard_3D_Animation_Model *model = NULL;
		if(type <= egypt3d_fly_machine)
			model = NETLizard_ReadGLEgypt3DRoleModelFile(r -> mesh_file, atoi(r -> tex_file));
		else
		{
			model = NETLizard_ReadGLClone3DRoleModelFile(r -> mesh_file, atoi(r -> tex_file));
			if(type >= clone3d_soldier && type <= clone3d_soldier2)
			{
				if(glIsTexture(model -> tex -> texid))
				{
					glDeleteTextures(1, &model -> tex -> texid);
				}
				free(model -> tex);
				char *name = NEW_II(char, strlen(_KARIN_GAME_DIR) + 1 + 17 + 1);
				sprintf(name, "%s/clone3d/w/w%s.png", _KARIN_GAME_DIR, r -> tex_file);
				model -> tex = new_texture_from_nl_v3_3d_file(name);
				free(name);
			}
		}

		if(!model)
		{
			game_model -> source = unavailable_model_type;
			return 0;
		}
		else
		{
			game_model -> netlizard_character.source = netlizard_model_type;
			game_model -> netlizard_character.model = model;
			game_model -> netlizard_character.scale= r -> scale;
			game_model -> netlizard_character.z_offset = 90.0;
			return 1;
		}
	}
	else if(type >= caitlyn_original && type < lol_total_model)
	{
		const char *dds[1] = {r -> tex_file};
		LOL_Model *model = new_LOL_Model(r -> mesh_file, r -> anim_file, dds, 1);
		if(!model)
		{
			game_model -> source = unavailable_model_type;
			return 0;
		}
		else
		{
			game_model -> lol_character.source = lol_model_type;
			game_model -> lol_character.model = model;
			game_model -> lol_character.scale= r -> scale;
			game_model -> lol_character.x_offset = 90.0;
			int i;
			for(i = 0; i < LOL_Total_Type; i++)
			{
				if(model -> anim)
				{
					LOL_GetAnimationRangeByType(model, i, game_model -> lol_character.anim_list + i, NULL);
					//printfs(s);
				}
				else
					game_model -> lol_character.anim_list[i] = -1;
				//printf("%d, %d\n", i, game_model->lol_character.anim_list[i]);
			}
			return 1;
		}
	}
	else
		return 0;
}

void Game_FreeCharacterModel(game_character_model *game_model)
{
	if(!game_model)
		return;
	if(game_model -> source == lol_model_type)
	{
		delete_LOL_Model(game_model -> lol_character.model);
		free(game_model -> lol_character.model);
	}
	else if(game_model -> source == netlizard_model_type)
	{
		delete_GL_NETLizard_3D_Animation_Model(game_model -> netlizard_character.model);
		free(game_model -> netlizard_character.model);
	}
	else
		return;
}
