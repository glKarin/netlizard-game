#include "character.h"
#include "nl_std.h"
#include "netlizard/netlizard.h"
#include "game_util.h"

#include "opengl.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define JUMP_SPEED 230.0
#define MOVE_UNIT 800.0
#define TURN_UNIT 150.0

#define ANIMATION_MAX_DELTA 0.1

#define FRAME_FLOAT_TO_INT ceil //round

extern char shared_str[DEBUG_STRING_MAX_LENGTH];

typedef enum _status_compare_result
{
	status_compare_all_equals = 0,
	status_compare_only_leg_different,
	status_compare_only_body_different,
	status_compare_all_different,
	status_compare_num_different,
	status_compare_one_different,
	status_compare_type_different,
} status_compare_result;

typedef enum _compute_frame_result
{
	play_done_and_no_next_animation = -1,
	play_done_and_need_next_animation = -2
} compute_frame_result;

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

	{natasha2, NATASHA2_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{choijiyoon, CHOIJIYOON_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{jessica, JESSICA_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{jessica2, JESSICA2_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{lucia, LUCIA_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{natasha, NATASHA_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{choijiyoon2, CHOIJIYOON2_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{yuri2, YURI2_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{police, POLICE_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{mila, MILA_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{lisa, LISA_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},

	{TR1_terror, TR1_TERROR_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{TR2_leet, TR2_LEET_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{TR3_arctic, TR3_ARCTIC_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{TR4_guerilla, TR4_GUERILLA_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{TR5_militia, TR5_MILITIA_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{TR2_leet2, TR2_LEET2_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},

	{CT1_urban, CT1_URBAN_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{CT2_gsg9, CT2_GSG9_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{CT3_sas, CT3_SAS_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{CT4_gign, CT4_GIGN_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{CT5_spetsnaz, CT5_SPETSNAZ_MDL, NULL, NULL, NATASHA_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},

	{caitlyn_original, CAITLYN_ORIGINAL_MESH, CAITLYN_ORIGINAL_PNG, CAITLYN_ORIGINAL_ANIM, CAITLYN_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
	{jinx_original, JINX_ORIGINAL_MESH, JINX_ORIGINAL_PNG, JINX_ORIGINAL_ANIM, JINX_CHARACTER_SCALE, long_attack_type, 50, 180, 250, MOVE_UNIT, TURN_UNIT, JUMP_SPEED},
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

	"Natasha (Fashion edition)",
	"ChoiJiYoon",
	"Jessica",
	"Jessica (Soilder edition)",
	"Lucia",
	"Natasha",
	"ChoiJiYoon (Standard edition)",
	"Yuri (Student edition)",
	"Police",
	"Mila",
	"Lisa",

	"Terror",
	"Leet",
	"Arctic",
	"Guerilla",
	"Militia",
	"Leet 2",
	
	"Urban",
	"GSG9",
	"SAS",
	"GIGN",
	"Specnaz",

	"Caitlyn",
	"Jinx"
	/*
	"Caitlyn Safari",
	"Caitlyn Arctic Warfare",
	"Caitlyn Officer"
		*/
};

static unsigned Game_UpdateLolCharacterStatus(game_character_model *model, const weapon *wp, character_animation_data *data, unsigned status, animation_orientation_type o);
static unsigned Game_UpdateNETLizardCharacterStatus(game_character_model *model, const weapon *wp, character_animation_data *data, unsigned status, animation_orientation_type o);
static unsigned Game_UpdateCSOLCharacterStatus(game_character_model *model, const weapon *wp, character_animation_data *data, unsigned status, animation_orientation_type o);
static int Game_DeattachStatus(unsigned status, unsigned ret[character_all_part_type]);
static status_compare_result Game_CompareStatus(unsigned a, unsigned b);

// 计算理想中需要播放的帧数
void Game_ComputeAnimationPlayFrameCount(model_source_type source, character_animation_data *animation, int fps, float delta)
{
	//if(!model || !model->anim)
	if(!animation)
		return;
	if(source == unavailable_model_type)
		return;
	float dt = delta;
	if(dt > ANIMATION_MAX_DELTA)
		dt = ANIMATION_MAX_DELTA;
	unsigned int i;
	for(i = 0; i < animation->num; i++)
		animation->idata[i].comp = (float)animation->idata[i].fps * dt;
	animation->last_play_time += delta * 1000.0;
}

// 获取实际上需要播放的帧数
// -1 no next frame // -2 need next animation
void Game_GetAnimationNextFrame(character_animation_data *animation)
{
	if(!animation)
		return;
	unsigned int i;
	for(i = 0; i < animation->num; i++)
	{
		struct character_animation_internal_data *data = animation->idata + i;
		int f = (int)FRAME_FLOAT_TO_INT(data->comp);
		if(data->anim_orient == forward_play_type)
		{
			if(data->anim_loop == no_loop_type)
			{
				if(data->frame == data->frame_count - 1)
				{
					data->play = play_done_and_no_next_animation;
				}
				else if(data->frame + f >= data->frame_count - 1)
				{
					data->play = data->frame_count - 1;
				}
				else
				{
					data->play = data->frame + f;
				}
			}
			else if(data->anim_loop == one_animation_loop_type)
			{
				data->play = (data->frame + f) % data->frame_count;
			}
			else if(data->anim_loop == one_type_loop_type)
			{
				if(data->frame == data->frame_count - 1)
				{
					data->play = play_done_and_need_next_animation;
				}
				else if(data->frame + f >= data->frame_count - 1)
				{
					data->play = data->frame_count - 1;
				}
				else
				{
					data->play = data->frame + f;
				}
			}
		}
		else
		{
			if(data->anim_loop == no_loop_type)
			{
				if(data->frame == 0)
				{
					data->play = play_done_and_no_next_animation;
				}
				else if(data->frame - f <= 0)
				{
					data->play = 0;
				}
				else
				{
					data->play = data->frame - f;
				}
			}
			else if(data->anim_loop == one_animation_loop_type)
			{
				int p = data->frame - f;
				if(p > 0)
					data->play = p % data->frame_count;
				else if(p < 0)
					data->play = data->frame_count - KARIN_ABS(p % data->frame_count);
				else
					data->play = p;
			}
			else if(data->anim_loop == one_type_loop_type)
			{
				if(data->frame == 0)
				{
					data->play = play_done_and_need_next_animation;
				}
				else if(data->frame - f <= 0)
				{
					data->play = 0;
				}
				else
				{
					data->play = data->frame - f;
				}
			}
		}
	}
}

int Game_GetNETLizardAnimationIndex(GL_NETLizard_3D_Animation_Model *model, NETLizard_3D_Animation_Type type)
{
	if(!model || type == Animation_Unknow_Type)
		return -1;
	unsigned int i;
	for(i = 0; i < model->anim_count; i++)
	{
		if(model->animations[i].type == type)
			return i;
	}
	return -1;
}

// 更新角色当前的动作
int Game_UpdateCharacterStatus(game_character *gamer, unsigned status, animation_orientation_type o)
{
	if(!gamer)
		return 0;
	status_compare_result scr = Game_CompareStatus(status, gamer->current_status);
	unsigned up = 0;
	if(scr == status_compare_all_equals)
	{
#if 0
		if(gamer->model.source == lol_model_type)
		{
			if(wp && (status == attack_status_type || status == fighting_status_type))
			{
				float anf = ff * wp->firing_rate;
				f = (int)round(KARIN_MAX(anf, ff));
			}
			else if(wp && (status == reload_status_type || status == runreload_status_type))
			{
				float anf = ff * ((float)(gamer -> animation.frame_count / wp->reload_time) / (float)fps);
				//sprintf(shared_str, "%f - %f", f, anf);
				f = (int)round(KARIN_MAX(floor(anf), ff));
			}
		}
		else if(gamer->model.source == csol_model_type)
		{
			if(wp && (status == reload_status_type || status == runreload_status_type))
			{
				float anf = ff * ((float)(gamer -> animation.frame_count / wp->reload_time) / (float)fps);
				//float anf = f * ((float)gamer->animation.frame_count / (float)gamer->animation.fps) / gamer->current_weapon.reload_time;
				//sprintf(shared_str, "%f - %f", f, anf);
				f = (int)round(KARIN_MAX(floor(anf), ff));
			}
		}
#endif
		Game_GetAnimationNextFrame(&gamer->animation);
		unsigned int i;
		for(i = 0; i < gamer->animation.num; i++)
		{
			int n = gamer->animation.idata[i].play;
			if(n == play_done_and_need_next_animation)
			{
				up |= (1 << i);
				gamer->animation.idata[i].status = 0;
			}
			else if(n >= 0)
			{
				if(gamer->model.source == csol_model_type)
				{
					gamer->animation.idata[i].frame = (int)FRAME_FLOAT_TO_INT(CSOL_SetFrame(gamer->model.csol_character.model, gamer->animation.num == 1 ? ALL_PART : (1 << i), n));
				}
				else
					gamer->animation.idata[i].frame = n;
			}
			else
			{
				// don't need to play.
			}
		}
	}
	else
	{
		up = scr;
		/*
		int cs = Game_ChangeStatus(gamer->status, status) | 1;
		if(cs || gamer->animation.frame == gamer->animation.frame_count - 1)
		{
			Game_UpdateCharacterStatus(gamer, status);
		}
		else if(gamer->animation.frame + f >= gamer->animation.frame_count - 1)
		{
			if(gamer->model.source == csol_model_type)
			{
				/\*gamer->animation.frame = *\/SetFrame(gamer->model.csol_character.model, gamer->animation.frame_count - 1);
				gamer->animation.frame = gamer->animation.frame_count - 1;
			}
			else
				gamer->animation.frame = gamer->animation.frame_count - 1;
		}
		else
		{
			if(f > 0)
			{
				if(gamer->model.source == csol_model_type)
					gamer->animation.frame = (int)round(SetFrame(gamer->model.csol_character.model, gamer->animation.frame + ff));
				else
					gamer->animation.frame += f;
			}
		}
		*/
	}

	if(up == status_compare_all_equals)
	{
		if((status & run_status_type) && gamer->animation.idata[character_leg_part_type].anim_orient != o)
		{
			gamer->animation.idata[character_leg_part_type].anim_orient = o;
		}
		return 0;
	}

	const weapon *wp = Game_CharacterCurrentWeapon(gamer);
	if(gamer->model.source == lol_model_type)
	{
		if(!Game_UpdateLolCharacterStatus(&gamer->model, wp, &gamer->animation, status, o))
			return 0;
	}
	else if(gamer->model.source == netlizard_model_type)
	{
		if(!Game_UpdateNETLizardCharacterStatus(&gamer->model, wp, &gamer->animation, status, o))
			return 0;
	}
	else if(gamer->model.source == csol_model_type)
	{
		if(!Game_UpdateCSOLCharacterStatus(&gamer->model, wp, &gamer->animation, status, o))
			return 0;
	}
	else
		return 0;

	gamer->current_status = status;
	return 1;
}

game_character * new_csol_game_character(game_character *c, const char *mdlfile, float x, float y, float z, float xr, float yr, float f, float w, float h, float th, float mu, float tu, float speed, int scene)
{
	if(!mdlfile)
		return NULL;
	RETURN_PTR(gamer, c, game_character)	

		gamer->health = health_full_type;
	gamer->health_full = gamer->health;
	gamer->width = w;
	gamer->height = h;
	gamer->full_height = th;
	gamer->move_unit = mu;
	gamer->turn_unit = tu;
	gamer->z_jump_speed = speed;
	gamer->z_moving.state = no_z_type;
	gamer->z_moving.jump_speed = 0.0;
	gamer->z_moving.speed = 0.0;
	gamer->z_moving.start_time = 0;
	gamer->z_moving.start_z = 0;
	gamer->scene = scene;
	gamer->scene_collision_result = scene == -1 ? 0 : 2;
	gamer->collision_item = -1;
	gamer->score.kill = 0;
	gamer->score.death = 0;
	gamer->score.assist = 0;
	gamer->score.killed_character = -1;
	gamer->score.kill_character = -1;
	gamer->group = 0;
	gamer->index = 0;

	GameStudioModel *model = NEW(GameStudioModel);
	ZERO(model, GameStudioModel);
	unsigned b = CSOL_LoadMDL(model, mdlfile);
	if(!b)
	{
		gamer->model.source = unavailable_model_type;
		free(model);
	}
	else
	{
		gamer->model.csol_character.source = csol_model_type;
		gamer->model.csol_character.model = model;
		gamer->model.csol_character.scale = f;
		gamer->model.csol_character.z_offset = 90.0;
		gamer->model.csol_character.y_offset = 180.0;
	}

	gamer->weapons.current_weapon = -1;

	Game_UpdateCharacterPositionAndDirection(gamer, x, y, z, xr, yr, 1);
	Game_UpdateCharacterStatus(gamer, idle_status_type, forward_play_type);
	AI_MakeComputeAction(&gamer->ai, 0, aiaction_idle_type);
	return gamer;
}

game_character * new_lol_game_character(game_character *c, const char *meshf, const char *ddsf[], int count, const char *animf, float x, float y, float z, float xr, float yr, float f, float w, float h, float th, float mu, float tu, float speed, int scene)
{
	if(!meshf || !animf)
		return NULL;
	RETURN_PTR(gamer, c, game_character)	

		gamer->health = health_full_type;
	gamer->health_full = gamer->health;
	gamer->width = w;
	gamer->height = h;
	gamer->full_height = th;
	gamer->move_unit = mu;
	gamer->turn_unit = tu;
	gamer->z_jump_speed = speed;
	gamer->z_moving.state = no_z_type;
	gamer->z_moving.jump_speed = 0.0;
	gamer->z_moving.speed = 0.0;
	gamer->z_moving.start_time = 0;
	gamer->z_moving.start_z = 0;
	gamer->scene = scene;
	gamer->scene_collision_result = scene == -1 ? 0 : 2;
	gamer->collision_item = -1;
	gamer->score.kill = 0;
	gamer->score.death = 0;
	gamer->score.assist = 0;
	gamer->score.killed_character = -1;
	gamer->score.kill_character = -1;
	gamer->group = 0;
	gamer->index = 0;

	LOL_Model *model = new_LOL_Model(meshf, animf, ddsf, count);
	if(!model)
	{
		gamer->model.source = unavailable_model_type;
	}
	else
	{
		gamer->model.lol_character.source = lol_model_type;
		gamer->model.lol_character.model = model;
		gamer->model.lol_character.scale= f;
		gamer->model.lol_character.x_offset = 90.0;
		int i;
		for(i = 0; i < LOL_Total_Type; i++)
		{
			if(model->anim)
			{
				LOL_GetAnimationRangeByType(model, i, gamer->model.lol_character.anim_list + i, NULL);
				//printfs(s);
			}
			else
				gamer->model.lol_character.anim_list[i] = -1;
		}
	}

	gamer->weapons.current_weapon = -1;

	Game_UpdateCharacterPositionAndDirection(gamer, x, y, z, xr, yr, 1);
	Game_UpdateCharacterStatus(gamer, idle_status_type, forward_play_type);
	AI_MakeComputeAction(&gamer->ai, 0, aiaction_idle_type);
	return gamer;
}

void Game_RenderGameCharacter(const game_character *gamer)
{
	if(!gamer)
		return;
	const weapon *wp = Game_CharacterCurrentWeapon((game_character *)gamer);
	if(gamer->model.source == lol_model_type)
	{
		if(!gamer->model.lol_character.model)
			return;
		glPushMatrix();
		{
			glTranslatef(gamer->position[0], gamer->position[1], gamer->position[2]);
			glRotatef(gamer->model.lol_character.x_offset, 1.0, 0.0, 0.0);
			glRotatef(gamer->y_angle, 0.0f, 1.0f, 0.0f);

			if(gamer->model.lol_character.scale != 1.0)
				glScalef(gamer->model.lol_character.scale, gamer->model.lol_character.scale, gamer->model.lol_character.scale);
			LOL_RenderModel(gamer->model.lol_character.model, 1, gamer->animation.idata[0].anim, gamer->animation.idata[0].frame);
			//GLfloat yr = Algo_FormatAngle(-gamer->y_angle - 180.0);
			//glRotatef(90.0, 1.0, 0.0, 0.0);
			//glRotatef(yr, 0.0f, 1.0f, 0.0f);
		}
		glPopMatrix();
	}

	else if(gamer->model.source == netlizard_model_type)
	{
		if(!gamer->model.netlizard_character.model)
			return;
		if(wp && wp->model && wp->model->tp_model)
		{
			glPushMatrix();
			{
				if(gamer->current_status & attack_status_type)
				{
					glTranslatef(wp->render_position[0], wp->render_position[1], wp->render_position[2]);
					glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
					glTranslatef(0.0, gamer->width, 0.0);
					glTranslatef(wp->model->position[0], wp->model->position[1], wp->model->position[2]);
					if((IS_NEAR_WEAPON(*wp)) || (IS_GRENADE_WEAPON(*wp)))
						glTranslatef(0.0, -90.0, 0.0);
				}
				else if(gamer->current_status == death_status_type)
				{
					glTranslatef(gamer->position[0], gamer->position[1], gamer->position[2]);
					glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
					glTranslatef(wp->model->position[0], wp->model->position[1], wp->model->position[2]);
				}
				else
				{
					if((IS_NEAR_WEAPON(*wp)) || (IS_GRENADE_WEAPON(*wp)))
					{
						glTranslatef(gamer->position[0], gamer->position[1], gamer->position[2] + gamer->full_height / 2);
						glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
						glRotatef(90.0, 1.0f, 0.0f, 0.0f);
						glTranslatef(-30.0, 0.0, 0.0);
						glTranslatef(0.0, 0.0, wp->model->position[2]);
					}
					else if((IS_LONG_WEAPON(*wp)) || (IS_LAUNCHER_WEAPON(*wp)))
					{
						glTranslatef(wp->render_position[0], wp->render_position[1], wp->render_position[2]);
						glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
						glTranslatef(0.0, gamer->width, 0.0);
						glRotatef(90.0, 1.0f, 0.0f, 0.0f);
						glRotatef(90.0, 0.0f, 1.0f, 0.0f);
						glTranslatef(30.0, 0.0, 0.0);
						glTranslatef(0.0, 0.0, wp->model->position[2]);
					}
				}
				glRotatef(wp->model->tp_model->item_meshes[0].angle[0], 1.0f, 0.0f, 0.0f);
				glRotatef(wp->model->tp_model->item_meshes[0].angle[1], 0.0f, 0.0f, 1.0f);
				if(wp->model->scale != 1.0)
					glScalef(wp->model->scale, wp->model->scale, wp->model->scale);
				glPushAttrib(GL_POLYGON_BIT);
				{
					oglDisable(GL_CULL_FACE);
					//NETLizard_RenderGL3DModel(wp->model.tp_model);
					NETLizard_RenderGL3DMesh(&(wp->model->tp_model->item_meshes[0].item_mesh), wp->model->tp_model->texes);
				}
				glPopAttrib();
			}
			glPopMatrix();
		}

		glPushMatrix();
		{
			glTranslatef(gamer->position[0], gamer->position[1], gamer->position[2]);
			//glRotatef(gamer->x_angle, 1.0f, 0.0f, 0.0f);
			glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
			glRotatef(gamer->model.netlizard_character.z_offset, 0.0f, 0.0f, 1.0f);
			//glRotatef(-90.0, 0.0f, 0.0f, 1.0f);
			if(gamer->model.netlizard_character.scale != 1.0)
				glScalef(gamer->model.netlizard_character.scale, gamer->model.netlizard_character.scale, gamer->model.netlizard_character.scale);
			NETLizard_RenderGL3DAnimationModel(gamer->model.netlizard_character.model, gamer->animation.idata[0].anim, gamer->animation.idata[0].frame);
		}
		glPopMatrix();
	}

	else if(gamer->model.source == csol_model_type)
	{
		if(!gamer->model.csol_character.model)
			return;
		if(wp && wp->model && wp->model->tp_model)
		{
			glPushMatrix();
			{
				if(gamer->current_status & attack_status_type)
				{
					glTranslatef(wp->render_position[0], wp->render_position[1], wp->render_position[2]);
					glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
					glTranslatef(0.0, gamer->width, 0.0);
					glTranslatef(wp->model->position[0], wp->model->position[1], wp->model->position[2]);
					if((IS_NEAR_WEAPON(*wp)) || (IS_GRENADE_WEAPON(*wp)))
						glTranslatef(0.0, -90.0, 0.0);
				}
				else if(gamer->current_status == death_status_type)
				{
					glTranslatef(gamer->position[0], gamer->position[1], gamer->position[2]);
					glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
					glTranslatef(wp->model->position[0], wp->model->position[1], wp->model->position[2]);
				}
				else
				{
					if((IS_NEAR_WEAPON(*wp)) || (IS_GRENADE_WEAPON(*wp)))
					{
						glTranslatef(gamer->position[0], gamer->position[1], gamer->position[2] + gamer->full_height / 2);
						glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
						glRotatef(90.0, 1.0f, 0.0f, 0.0f);
						glTranslatef(-30.0, 0.0, 0.0);
						glTranslatef(0.0, 0.0, wp->model->position[2]);
					}
					else if((IS_LONG_WEAPON(*wp)) || (IS_LAUNCHER_WEAPON(*wp)))
					{
						glTranslatef(wp->render_position[0], wp->render_position[1], wp->render_position[2]);
						glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
						glTranslatef(0.0, gamer->width, 0.0);
						glRotatef(90.0, 1.0f, 0.0f, 0.0f);
						glRotatef(90.0, 0.0f, 1.0f, 0.0f);
						glTranslatef(30.0, 0.0, 0.0);
						glTranslatef(0.0, 0.0, wp->model->position[2]);
					}
				}
				glRotatef(wp->model->tp_model->item_meshes[0].angle[0], 1.0f, 0.0f, 0.0f);
				glRotatef(wp->model->tp_model->item_meshes[0].angle[1], 0.0f, 0.0f, 1.0f);
				if(wp->model->scale != 1.0)
					glScalef(wp->model->scale, wp->model->scale, wp->model->scale);
				glPushAttrib(GL_POLYGON_BIT);
				{
					oglDisable(GL_CULL_FACE);
					//NETLizard_RenderGL3DModel(wp->model.tp_model);
					NETLizard_RenderGL3DMesh(&(wp->model->tp_model->item_meshes[0].item_mesh), wp->model->tp_model->texes);
				}
				glPopAttrib();
			}
			glPopMatrix();
		}

		glPushMatrix();
		{
			glTranslatef(gamer->position[0], gamer->position[1], gamer->position[2]);
			glTranslatef(0.0, 0.0, (float)HL_MDL_Z_TRANSLATE * gamer->model.csol_character.scale);
			//glRotatef(gamer->x_angle, 1.0f, 0.0f, 0.0f);
			glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
			glRotatef(gamer->model.csol_character.z_offset, 0.0f, 0.0f, 1.0f);
			glRotatef(gamer->model.csol_character.y_offset, 0.0f, 0.0f, 1.0f);
			if(gamer->model.csol_character.scale != 1.0)
				glScalef(gamer->model.csol_character.scale, gamer->model.csol_character.scale, gamer->model.csol_character.scale);
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			{
				CSOL_DrawModel(gamer->model.csol_character.model);
			}
			glPopAttrib();
		}
		glPopMatrix();
	}
	else
		return;
}

// 更新角色状态，动画数据, 外部调用
void Game_CharacterPlayAnimation(game_character *gamer, long long time, int fps, float delta)
{
	if(!gamer)
		return;
	if(gamer->model.source == unavailable_model_type)
		return;
	const weapon *wp = Game_CharacterCurrentWeapon(gamer);
	Game_ComputeAnimationPlayFrameCount(gamer->model.source, &gamer->animation, fps, delta);
	unsigned status = 0;
	animation_orientation_type o = forward_play_type;
	if(gamer->health == health_death_type)
	{
		gamer->health = health_death_type;
		status = death_status_type;
	}
	else
	{
		if(gamer->ai.type != ai_player_type)
			AI_ProcessAction(&gamer->ai, time);
		ai_action_type a = gamer->ai.action;
		if(wp && (a & aiaction_reload_type) && wp->status == reload_type)
		{
			status |= reload_status_type;
		}
		else if(wp && (a & aiaction_attack_type) && !((wp->status == outofammo_type || wp->status == reload_type)))
		{
			status |= attack_status_type;
		}

		if(a & aiaction_jump_type)
			status |= jump_status_type;
		else if(a & aiaction_movexyz_type || a & aiaction_turny_type)
			status |= run_status_type;
		else if(a == aiaction_idle_type || a == aiaction_stand_type)
			status |= idle_status_type;

		if(status == 0)
			status = idle_status_type;

		if((status & run_status_type) && (a & aiaction_movebackward_type))
			o = backward_play_type;
	}

	Game_UpdateCharacterStatus(gamer, status, o);
}

game_character * new_netlizard_game_character(game_character *c, const char *game, const char *file, int index, float x, float y, float z, float xr, float yr, float f, float w, float h, float th, float mu, float tu, float speed, int scene)
{
	if(!file || index < 0 || !game)
		return NULL;

	RETURN_PTR(gamer, c, game_character)	

		gamer->health = health_full_type;
	gamer->health_full = gamer->health;
	gamer->width = w;
	gamer->height = h;
	gamer->full_height = th;
	gamer->move_unit = mu;
	gamer->turn_unit = tu;
	gamer->z_jump_speed = speed;
	gamer->z_moving.state = no_z_type;
	gamer->z_moving.jump_speed = 0.0;
	gamer->z_moving.speed = 0.0;
	gamer->z_moving.start_z = 0;
	gamer->z_moving.start_time = 0;
	gamer->scene = scene;
	gamer->scene_collision_result = scene == -1 ? 0 : 2;
	gamer->collision_item = -1;
	gamer->score.kill = 0;
	gamer->score.death = 0;
	gamer->score.assist = 0;
	gamer->group = 0;
	gamer->index = 0;

	GL_NETLizard_3D_Animation_Model *model = NULL;
	if(strcasecmp(game, "egypt3d") == 0)
		model = NETLizard_ReadGLEgypt3DRoleModelFile(file, index);
	else if(strcasecmp(game, "clone3d") == 0)
		model = NETLizard_ReadGLClone3DRoleModelFile(file, index);
	else
		gamer->model.source = unavailable_model_type;

	if(!model)
	{
		gamer->model.source = unavailable_model_type;
	}
	else
	{
		gamer->model.netlizard_character.source = netlizard_model_type;
		gamer->model.netlizard_character.model = model;
		gamer->model.netlizard_character.scale= f;
		gamer->model.netlizard_character.z_offset = 90.0;
	}

	gamer->weapons.current_weapon = -1;

	Game_UpdateCharacterPositionAndDirection(gamer, x, y, z, xr, yr, 1);
	Game_UpdateCharacterStatus(gamer, idle_status_type, forward_play_type);
	AI_MakeComputeAction(&gamer->ai, 0, aiaction_idle_type);
	return gamer;
}

void delete_game_character(game_character *gamer)
{
	if(!gamer)
		return;
	FREE_PTR(gamer->name);
	delete_game_ai(&gamer->ai);
	Game_FreeCharacterWeapons(gamer);
	Game_FreeCharacterModel(&gamer->model);
}

void Game_UpdateCharacterPositionAndDirection(game_character *gamer, float x, float y, float z, float xr, float yr, unsigned up_wp)
{
	if(!gamer)
		return;
	gamer->position[0] = x;
	gamer->position[1] = y;
	gamer->position[2] = z;
	gamer->x_angle = xr;
	gamer->y_angle = yr;
	nl_vector3_t dir = Algo_ComputeDirection(gamer->y_angle, gamer->x_angle);
	gamer->direction[0] = dir.x;
	gamer->direction[1] = dir.y;
	gamer->direction[2] = dir.z;
	weapon *wp = Game_CharacterCurrentWeapon(gamer);
	if(!wp)
		return;
	dir = Vector3_Scale(&dir, gamer->width);
	vector3_t v = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};
	dir = Vector3_PlusVector3(&v, &dir);
	wp->render_position[0] = dir.x;
	wp->render_position[1] = dir.y;
	wp->render_position[2] = dir.z;

	wp->position[0] = dir.x;
	wp->position[1] = dir.y;
	wp->position[2] = dir.z + gamer->weapons.wpon_z_fixed;

	if(up_wp)
	{
		wp->x_angle = gamer->x_angle;
		wp->y_angle = gamer->y_angle;
	}
}

void Game_UpdateCharacterCurrentWeaponPositionAndDirection(game_character *gamer)
{
	if(!gamer)
		return;
	weapon *wp = Game_CharacterCurrentWeapon(gamer);
	if(!wp)
		return;
	nl_vector3_t dir = Algo_ComputeDirection(gamer->y_angle, gamer->x_angle);
	dir = Vector3_Scale(&dir, gamer->width);
	vector3_t v = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};
	dir = Vector3_PlusVector3(&v, &dir);
	wp->render_position[0] = dir.x;
	wp->render_position[1] = dir.y;
	wp->render_position[2] = dir.z;

	wp->position[0] = dir.x;
	wp->position[1] = dir.y;
	wp->position[2] = dir.z + gamer->weapons.wpon_z_fixed;

	wp->x_angle = gamer->x_angle;
	wp->y_angle = gamer->y_angle;
}

game_character * new_game_character(game_character *c, int type, float x, float y, float z, float xr, float yr, int id, const char *name, int scene, const weapon_model_type wt[], unsigned int max)
{
	RETURN_PTR(gamer, c, game_character)

		const game_model_resource *r = Game_Model_Resource + type;
	if(type >= egypt3d_worm && type <= egypt3d_fly_machine)
	{
		new_netlizard_game_character(gamer, "egypt3d", r->mesh_file, atoi(r->tex_file), x, y, z, xr, yr, r->scale, r->width, r->height, r->full_height, r->move_unit, r->turn_unit, r->jump_speed, scene);
		const weapon_model_type Types[] = {egypt3d_Worm_Weapon + egypt3d_worm};
		Game_GetWeapon(gamer, Types, 1);
	}
	else if(type >= clone3d_human_cloning && type <= clone3d_soldier2)
	{
		new_netlizard_game_character(gamer, "clone3d", r->mesh_file, 1, x, y, z, xr, yr, r->scale, r->width, r->height, r->full_height, r->move_unit, r->turn_unit, r->jump_speed, scene);
		if(type != clone3d_human_cloning)
		{
			GL_NETLizard_3D_Animation_Model *model = gamer->model.netlizard_character.model;
			if(glIsTexture(model->tex->texid))
			{
				glDeleteTextures(1, &model->tex->texid);
			}
			free(model->tex);
			char *name = NEW_II(char, strlen(_KARIN_GAME_DIR) + 1 + 17 + 1);
			sprintf(name, "%s/clone3d/w/w%s.png", _KARIN_GAME_DIR, r->tex_file);
			model->tex = new_texture_from_nl_v3_3d_file(name);
			free(name);
		}
		if(wt && max > 0)
			Game_GetWeapon(gamer, wt, max);
	}
	else if(type >= clone3d_bio_soldier && type <= clone3d_machine)
	{
		new_netlizard_game_character(gamer, "clone3d", r->mesh_file, atoi(r->tex_file), x, y, z, xr, yr, r->scale, r->width, r->height, r->full_height, r->move_unit, r->turn_unit, r->jump_speed, scene);
		if(type == clone3d_machine)
		{
			const weapon_model_type Types[] = { clone3d_Machine_Weapon};
			Game_GetWeapon(gamer, Types, 1);
		}
		else
		{
			if(wt && max > 0)
				Game_GetWeapon(gamer, wt, max);
		}
	}
	else if(type >= natasha2 && type < csol_total_model)
	{
		new_csol_game_character(gamer, r->mesh_file, x, y, z, xr, yr, r->scale, r->width, r->height, r->full_height, r->move_unit, r->turn_unit, r->jump_speed, scene);
		if(wt && max > 0)
			Game_GetWeapon(gamer, wt, max);
	}
	else
	{
		const char *dds[1] = {r->tex_file};
		new_lol_game_character(gamer, r->mesh_file, dds, 1, r->anim_file, x, y, z, xr, yr, r->scale, r->width, r->height, r->full_height, r->move_unit, r->turn_unit, r->jump_speed, scene);
		if(wt && max > 0)
			Game_GetWeapon(gamer, wt, max);
	}
	gamer->index = id;
	if(name)
		gamer->name = strdup(name);
	else
	{
		char *in = itostr(gamer->index);
		gamer->name = NEW_II(char, strlen(in) + strlen("Character") + 2);
		sprintf(gamer->name, "Character-%s", in);
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
			model = NETLizard_ReadGLEgypt3DRoleModelFile(r->mesh_file, atoi(r->tex_file));
		else
		{
			model = NETLizard_ReadGLClone3DRoleModelFile(r->mesh_file, atoi(r->tex_file));
			if(type >= clone3d_soldier && type <= clone3d_soldier2)
			{
				if(glIsTexture(model->tex->texid))
				{
					glDeleteTextures(1, &model->tex->texid);
				}
				free(model->tex);
				char *name = NEW_II(char, strlen(_KARIN_GAME_DIR) + 1 + 17 + 1);
				sprintf(name, "%s/clone3d/w/w%s.png", _KARIN_GAME_DIR, r->tex_file);
				model->tex = new_texture_from_nl_v3_3d_file(name);
				free(name);
			}
		}

		if(!model)
		{
			game_model->source = unavailable_model_type;
			return 0;
		}
		else
		{
			game_model->netlizard_character.source = netlizard_model_type;
			game_model->netlizard_character.model = model;
			game_model->netlizard_character.scale= r->scale;
			game_model->netlizard_character.z_offset = 90.0;
			return 1;
		}
	}
	else if(type >= natasha2 && type < csol_total_model)
	{
		GameStudioModel *model = NEW(GameStudioModel);
		ZERO(model, GameStudioModel);
		unsigned b = CSOL_LoadMDL(model, r->mesh_file);
		if(!b)
		{
			game_model->source = unavailable_model_type;
			free(model);
			return 0;
		}
		else
		{
			game_model->csol_character.source = csol_model_type;
			game_model->csol_character.model = model;
			game_model->csol_character.scale= r->scale;
			game_model->csol_character.z_offset = 90.0;
			game_model->csol_character.y_offset = 180.0;
			return 1;
		}
	}
	else if(type >= caitlyn_original && type < lol_total_model)
	{
		const char *dds[1] = {r->tex_file};
		LOL_Model *model = new_LOL_Model(r->mesh_file, r->anim_file, dds, 1);
		if(!model)
		{
			game_model->source = unavailable_model_type;
			return 0;
		}
		else
		{
			game_model->lol_character.source = lol_model_type;
			game_model->lol_character.model = model;
			game_model->lol_character.scale= r->scale;
			game_model->lol_character.x_offset = 90.0;
			int i;
			for(i = 0; i < LOL_Total_Type; i++)
			{
				if(model->anim)
				{
					LOL_GetAnimationRangeByType(model, i, game_model->lol_character.anim_list + i, NULL);
					//printfs(s);
				}
				else
					game_model->lol_character.anim_list[i] = -1;
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
	if(game_model->source == lol_model_type)
	{
		delete_LOL_Model(game_model->lol_character.model);
		free(game_model->lol_character.model);
	}
	else if(game_model->source == netlizard_model_type)
	{
		delete_GL_NETLizard_3D_Animation_Model(game_model->netlizard_character.model);
		free(game_model->netlizard_character.model);
	}
	else if(game_model->source == csol_model_type)
	{
		CSOL_FreeMDL(game_model->csol_character.model);
		free(game_model->csol_character.model);
	}
	else
		return;
}

void Game_FreeCharacterWeapons(game_character *gamer)
{
	if(!gamer)
		return;
	if(!gamer->weapons.wpons)
		return;
	unsigned int i;
	for(i = 0; i < gamer->weapons.wp_count; i++)
	{
		delete_weapon(gamer->weapons.wpons + i);
	}
	free(gamer->weapons.wpons);
	gamer->weapons.wpons = NULL;
	gamer->weapons.mask = 0;
	gamer->weapons.wp_count = 0;
	gamer->weapons.current_weapon = -1;
}

int Game_GetWeapon(game_character *gamer, const weapon_model_type types[], unsigned int count)
{
	if(!gamer || !types || count == 0)
		return -1;
	Game_FreeCharacterWeapons(gamer);
	gamer->weapons.wp_count = count;
	gamer->weapons.wpons = NEW_II(weapon, gamer->weapons.wp_count);
	unsigned mask = 0;
	unsigned int i;
	for(i = 0; i < count; i++)
	{
		new_weapon(gamer->weapons.wpons + i, types[i]);
		if(IS_LONG_WEAPON(gamer->weapons.wpons[i]) || IS_LAUNCHER_WEAPON(gamer->weapons.wpons[i]))
		{
			if(mask & main_weapon_1)
				mask |= main_weapon_2;
			else
				mask |= main_weapon_1;
		}
		else if(types[i] == pistol_gun_type)
			mask |= secondary_weapon;
		else if(types[i] == dagger_type)
			mask |= fighting_weapon;
		else if(IS_GRENADE_WEAPON(gamer->weapons.wpons[i]))
			mask |= launch_weapon;
		else
			mask |= other_weapon;
	}
	gamer->weapons.mask = mask;
	gamer->weapons.current_weapon = 0;
	Game_PreferWeapon(gamer);
	return gamer->weapons.wp_count;
}

weapon * Game_CharacterCurrentWeapon(game_character *gamer)
{
	if(!gamer)
		return NULL;
	if(!gamer->weapons.wpons || gamer->weapons.wp_count == 0)
		return NULL;
	if(gamer->weapons.current_weapon < 0)
		return NULL;
	return gamer->weapons.wpons + gamer->weapons.current_weapon;
}

int Game_PrevWeapon(game_character *gamer, unsigned skip)
{
	if(!gamer)
		return -1;
	if(!gamer->weapons.wpons || gamer->weapons.wp_count == 0)
		return -1;
	int c = gamer->weapons.current_weapon;
	if(c == 0)
		c = gamer->weapons.wp_count - 1;
	else if(c < 0)
		c = 0;
	else
		c--;
	gamer->weapons.current_weapon = c;
	if(skip)
	{
		int sc = c;
		do
		{
			if(gamer->weapons.wpons[c].ammo_total_count != 0 || gamer->weapons.wpons[c].type <= short_attack_type)
			{
				break;
			}
			if(c == 0)
				c = gamer->weapons.wp_count - 1;
			else if(c < 0)
				c = 0;
			else
				c--;
		}
		while(sc != c);
		gamer->weapons.current_weapon = c;
	}
	Game_UpdateCharacterCurrentWeaponPositionAndDirection(gamer);
	return gamer->weapons.current_weapon;
}

int Game_NextWeapon(game_character *gamer, unsigned skip)
{
	if(!gamer)
		return -1;
	if(!gamer->weapons.wpons || gamer->weapons.wp_count == 0)
		return -1;
	int c = gamer->weapons.current_weapon;
	if(c >= (int)(gamer->weapons.wp_count - 1))
		c = 0;
	else if(c < 0)
		c = 0;
	else
		c++;
	gamer->weapons.current_weapon = c;
	if(skip)
	{
		int sc = c;
		do
		{
			if(gamer->weapons.wpons[c].ammo_total_count != 0 || gamer->weapons.wpons[c].type <= short_attack_type)
			{
				break;
			}
			if(c >= (int)(gamer->weapons.wp_count - 1))
				c = 0;
			else if(c < 0)
				c = 0;
			else
				c++;
		}
		while(sc != c);
		gamer->weapons.current_weapon = c;
	}
	Game_UpdateCharacterCurrentWeaponPositionAndDirection(gamer);
	return gamer->weapons.current_weapon;
}

int Game_PreferWeapon(game_character *gamer)
{
	if(!gamer)
		return -1;
	if(!gamer->weapons.wpons || gamer->weapons.wp_count == 0)
		return -1;

	if((gamer->weapons.mask & main_weapon_1) && MAIN_WEAPON_1_INDEX < gamer->weapons.wp_count)
	{
		if(gamer->weapons.wpons[MAIN_WEAPON_1_INDEX].ammo_total_count != 0)
		{
			gamer->weapons.current_weapon = MAIN_WEAPON_1_INDEX;
			Game_UpdateCharacterCurrentWeaponPositionAndDirection(gamer);
			return gamer->weapons.current_weapon;
		}
	}
	if((gamer->weapons.mask & main_weapon_2) && MAIN_WEAPON_2_INDEX < gamer->weapons.wp_count)
	{
		if(gamer->weapons.wpons[MAIN_WEAPON_2_INDEX].ammo_total_count != 0)
		{
			gamer->weapons.current_weapon = MAIN_WEAPON_2_INDEX;
			Game_UpdateCharacterCurrentWeaponPositionAndDirection(gamer);
			return gamer->weapons.current_weapon;
		}
	}
	if((gamer->weapons.mask & secondary_weapon) && SECONDARY_WEAPON_INDEX < gamer->weapons.wp_count)
	{
		if(gamer->weapons.wpons[SECONDARY_WEAPON_INDEX].ammo_total_count != 0)
		{
			gamer->weapons.current_weapon = SECONDARY_WEAPON_INDEX;
			Game_UpdateCharacterCurrentWeaponPositionAndDirection(gamer);
			return gamer->weapons.current_weapon;
		}
	}
	if((gamer->weapons.mask & launch_weapon) && LAUNCH_WEAPON_INDEX < gamer->weapons.wp_count)
	{
		if(gamer->weapons.wpons[LAUNCH_WEAPON_INDEX].ammo_total_count != 0)
		{
			gamer->weapons.current_weapon = LAUNCH_WEAPON_INDEX;
			Game_UpdateCharacterCurrentWeaponPositionAndDirection(gamer);
			return gamer->weapons.current_weapon;
		}
	}
	if((gamer->weapons.mask & fighting_weapon) && FIGHTING_WEAPON_INDEX < gamer->weapons.wp_count)
	{
		gamer->weapons.current_weapon = FIGHTING_WEAPON_INDEX;
		Game_UpdateCharacterCurrentWeaponPositionAndDirection(gamer);
		return gamer->weapons.current_weapon;
	}
	Game_UpdateCharacterCurrentWeaponPositionAndDirection(gamer);
	return gamer->weapons.current_weapon;
}

unsigned Game_UpdateLolCharacterStatus(game_character_model *model, const weapon *wp, character_animation_data *data, unsigned status, animation_orientation_type o)
{
	if(!model || !data)
		return 0;
	if(model->source != lol_model_type)
		return 0;

	lol_game_character *m = &(model->lol_character);
	if(!m->model || !m->model->anim)
		return 0;

	int anim = -1;
	int frame_count = -1;
	if(status == death_status_type)
	{
		anim = m->anim_list[LOL_Death_Type];
	}
	else if(status & reload_status_type)
	{
		anim = m->anim_list[LOL_Idle3_Type];
		frame_count = 83; // idle 3 160 / 340
	}
	else if(status & attack_status_type)
	{
		if(wp)
		{
			if(IS_LONG_WEAPON(*wp))   
				anim = m->anim_list[LOL_Attack1_Type];
			else if(IS_LAUNCHER_WEAPON(*wp))    
				anim = m->anim_list[LOL_Attack2_Type];
			else if(IS_NEAR_WEAPON(*wp))    
				anim = m->anim_list[LOL_Attack3_Type];
			else if(IS_GRENADE_WEAPON(*wp))    
				anim = m->anim_list[LOL_Attack4_Type];
			else
				anim = m->anim_list[LOL_Attack1_Type];
		}
		else
			anim = m->anim_list[LOL_Attack1_Type];
	}
	else if(status & run_status_type || status & jump_status_type)
	{
		if(wp)
		{
			if(IS_LONG_WEAPON(*wp))   
				anim = m->anim_list[LOL_Run1_Type];
			else if(IS_LAUNCHER_WEAPON(*wp))    
				anim = m->anim_list[LOL_Run2_Type];
			else if(IS_NEAR_WEAPON(*wp))    
				anim = m->anim_list[LOL_Run3_Type];
			else if(IS_GRENADE_WEAPON(*wp))    
				anim = m->anim_list[LOL_Run4_Type];
			else
				anim = m->anim_list[LOL_Run1_Type];
		}
		else
			anim = m->anim_list[LOL_Run1_Type];
	}
	else
	{
		if(wp)
		{
			if(IS_LONG_WEAPON(*wp))   
				anim = m->anim_list[LOL_Idle1_Type];
			else if(IS_LAUNCHER_WEAPON(*wp))    
				anim = m->anim_list[LOL_Idle2_Type];
			else if(IS_NEAR_WEAPON(*wp))    
				anim = m->anim_list[LOL_Idle3_Type];
			else if(IS_GRENADE_WEAPON(*wp))    
				anim = m->anim_list[LOL_Idle4_Type];
			else
				anim = m->anim_list[LOL_Idle1_Type];
		}
		else
			anim = m->anim_list[LOL_Idle1_Type];
	}
	if(anim != -1)
	{
		data->idata[0].frame = 0;
		data->idata[0].anim = anim;
		data->idata[0].frame_count = frame_count == -1 ? (int)m->model->anim->animation[data->idata[0].anim].animation_bone[0].frame_count : frame_count;
		data->idata[0].anim_loop = Game_GetStatusAniamtionLoop(status);
		data->idata[0].fps = m->model->anim->animation[anim].fps;
		data->last_play_time = 0.0f;
		data->idata[0].play = 0;
		data->idata[0].comp = 0;
		data->idata[0].status = status;
		if(status == run_status_type && o == backward_play_type)
			data->idata[0].anim_orient = backward_play_type;
		else
			data->idata[0].anim_orient = forward_play_type;
		data->num = 1;
	}
	else
		return 0;
	return 1;
}

unsigned Game_UpdateNETLizardCharacterStatus(game_character_model *model, const weapon *wp, character_animation_data *data, unsigned status, animation_orientation_type o)
{
	if(!model || !data)
		return 0;
	if(model->source != netlizard_model_type)
		return 0;

	netlizard_game_character *m = &(model->netlizard_character);
	if(!m->model)
		return 0;

	int anim = -1;
	if(status == death_status_type)
	{
		int a1 = Game_GetNETLizardAnimationIndex(m->model, Animation_Dead1_Type);
		int a2 = Game_GetNETLizardAnimationIndex(m->model, Animation_Dead2_Type);
		if(a1 != -1 && a2 != -1)
			anim = rand() % 2 == 0 ? a1 : a2;
		else if(a1 != -1)
			anim = a1;
		else if(a2 != -1)
			anim = a2;
		else
			anim = -1;
	}
	else if(((status & attack_status_type) || (status & reload_status_type)) && ((status & run_status_type) == 0))
	{
		int a1 = Game_GetNETLizardAnimationIndex(m->model, Animation_Attack1_Type);
		int a2 = Game_GetNETLizardAnimationIndex(m->model, Animation_Attack2_Type);
		if(wp && ((IS_NEAR_WEAPON(*wp)) || (IS_GRENADE_WEAPON(*wp))))
			anim = a1;
		else if(wp && ((IS_LONG_WEAPON(*wp)) || (IS_LAUNCHER_WEAPON(*wp))))
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
	else if((status & run_status_type) || (status & jump_status_type))
	{
		if((status & attack_status_type) || (status & reload_status_type))
		{
			int a1 = Game_GetNETLizardAnimationIndex(m->model, Animation_Fighting1_Type);
			int a2 = Game_GetNETLizardAnimationIndex(m->model, Animation_Fighting2_Type);
			if(wp && ((IS_NEAR_WEAPON(*wp)) || (IS_GRENADE_WEAPON(*wp))))
				anim = a1;
			else if(wp && ((IS_LONG_WEAPON(*wp)) || (IS_LAUNCHER_WEAPON(*wp))))
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
			if(anim == -1)
				anim = Game_GetNETLizardAnimationIndex(m->model, Animation_Run_Type);
		}
		else
			anim = Game_GetNETLizardAnimationIndex(m->model, Animation_Run_Type);
	}
	else
	{
		anim = Game_GetNETLizardAnimationIndex(m->model, Animation_Idle_Type);
	}
	if(anim != -1)
	{
		data->idata[0].frame = 0;
		data->idata[0].anim = anim;
		data->idata[0].frame_count = m->model->animations[data->idata[0].anim].end - m->model->animations[data->idata[0].anim].begin + 1;
		data->idata[0].anim_loop = Game_GetStatusAniamtionLoop(status);
		data->idata[0].fps = NETLIZARD_ANIMATION_FPS;
		data->last_play_time = 0.0f;
		data->idata[0].play = 0;
		data->idata[0].comp = 0;
		data->idata[0].status = status;
		if((status & run_status_type) && o == backward_play_type)
			data->idata[0].anim_orient = backward_play_type;
		else
			data->idata[0].anim_orient = forward_play_type;
		data->num = 1;
	}
	else
		return 0;
	return 1;
}

unsigned Game_UpdateCSOLCharacterStatus(game_character_model *model, const weapon *wp, character_animation_data *data, unsigned status, animation_orientation_type o)
{
	if(!model || !data)
		return 0;
	if(model->source != csol_model_type)
		return 0;

	csol_game_character *m = &(model->csol_character);
	if(!m->model)
		return 0;

	unsigned int num = 0;
	int anim = -1;
	int leg_anim = -1;
	mstudioseqdesc_t *seq = NULL;
	mstudioseqdesc_t *leg_seq = NULL;
	unsigned s;
	unsigned leg_s;

	if(status == death_status_type)
	{
		const char *deaths[] = {
			"death1",
			"death2",
			"death3",
			"head",
			"gutshot",
			"left",
			"back",
			"right",
			"forward",
			//"crouch_die"
		};
		seq = leg_seq = CSOL_GetSequence(m->model, deaths[rand() % (countof(deaths))], &anim);
		num = 1;
		s = death_status_type;
	}
	else if(status == idle_status_type)
	{
		seq = leg_seq = CSOL_GetSequence(m->model, "idle1", &anim);
		num = 1;
		s = idle_status_type;
	}
	else
	{
		if(status & reload_status_type)
		{
			if(wp)
			{
				if(wp->type == shot_gun_type)
					seq = CSOL_GetSequence(m->model, "ref_reload_shotgun", &anim);
				else if(wp->type == mini_submachine_gun_type)
					seq = CSOL_GetSequence(m->model, "ref_reload_mp5", &anim);
				else	if(wp->type == automatic_rifle_type)
					seq = CSOL_GetSequence(m->model, "ref_reload_ak47", &anim);
				else if(wp->type == sniper_rifle_type)
					seq = CSOL_GetSequence(m->model, "ref_reload_rifle", &anim);
				else if(wp->type == machine_gun_type)   
					seq = CSOL_GetSequence(m->model, "ref_reload_m249", &anim);
				else if(IS_LAUNCHER_WEAPON(*wp))    
					seq = CSOL_GetSequence(m->model, "ref_reload_carbine", &anim);
				else if(IS_NEAR_WEAPON(*wp))    
					seq = CSOL_GetSequence(m->model, "ref_reload_onehanded", &anim);
				else if(IS_GRENADE_WEAPON(*wp))    
					seq = CSOL_GetSequence(m->model, "ref_aim_grenade", &anim);
				else
					seq = CSOL_GetSequence(m->model, "ref_aim_knife", &anim);
			}
			else
				seq = CSOL_GetSequence(m->model, "ref_aim_knife", &anim);
			s = reload_status_type;
		}
		else if(status & attack_status_type)
		{
			seq = CSOL_GetSequence(m->model, "idle1", &anim);
			s = attack_status_type;
		}
		else if(status & jump_status_type)
		{
			seq = CSOL_GetSequence(m->model, "jump", &anim);
			s = jump_status_type;
		}
		else if(status & run_status_type)
		{
			seq = CSOL_GetSequence(m->model, "run", &anim);
			s = run_status_type;
		}
		else
		{
			seq = CSOL_GetSequence(m->model, "idle1", &anim);
			s = idle_status_type;
		}

		if(status & jump_status_type)
		{
			leg_seq = CSOL_GetSequence(m->model, "jump", &leg_anim);
			leg_s = jump_status_type;
		}
		else if(status & run_status_type)
		{
			leg_seq = CSOL_GetSequence(m->model, "run", &leg_anim);
			leg_s = run_status_type;
		}
		else
		{
			leg_seq = CSOL_GetSequence(m->model, "idle1", &leg_anim);
			leg_s = idle_status_type;
		}

		num = 2;
	}

	if(seq && leg_seq)
	{
		if(num == 1)
		{
			/*
				 if(!seq)
				 {
				 seq = leg_seq;
				 anim = leg_anim;
				 leg_seq = NULL;
				 leg_anim = -1;
				 s = leg_s;
				 }
				 */
			data->idata[0].frame = 0;
			data->idata[0].anim = anim;
			data->idata[0].frame_count = seq->numframes;
			data->idata[0].anim_loop = Game_GetStatusAniamtionLoop(s);
			data->idata[0].fps = seq->fps;
			data->idata[0].play = 0;
			data->idata[0].comp = 0;
			data->idata[0].status = s;
			if(s == run_status_type)
				data->idata[0].anim_orient = o;
			else
				data->idata[0].anim_orient = forward_play_type;
			CSOL_SetSequence(m->model, ALL_PART, anim);
			data->idata[1].status = 0;
		}
		else
		{
			if(data->idata[character_body_part_type].status != s)
			{
				data->idata[character_body_part_type].frame = 0;
				data->idata[character_body_part_type].anim = anim;
				data->idata[character_body_part_type].frame_count = seq->numframes;
				data->idata[character_body_part_type].anim_loop = Game_GetStatusAniamtionLoop(s);
				data->idata[character_body_part_type].fps = seq->fps;
				data->idata[character_body_part_type].play = 0;
				data->idata[character_body_part_type].comp = 0;
				data->idata[character_body_part_type].status = s;
				data->idata[character_body_part_type].anim_orient = forward_play_type;
				CSOL_SetSequence(m->model, BODY_PART, anim);
			}

			if(data->num == 1 || data->idata[character_leg_part_type].status != leg_s)
			{
				data->idata[character_leg_part_type].frame = 0;
				data->idata[character_leg_part_type].anim = leg_anim;
				data->idata[character_leg_part_type].frame_count = leg_seq->numframes;
				data->idata[character_leg_part_type].anim_loop = Game_GetStatusAniamtionLoop(leg_s);
				data->idata[character_leg_part_type].fps = leg_seq->fps;
				data->idata[character_leg_part_type].play = 0;
				data->idata[character_leg_part_type].comp = 0;
				data->idata[character_leg_part_type].status = leg_s;
				if(leg_s & run_status_type)
					data->idata[character_leg_part_type].anim_orient = o;
				else
					data->idata[character_leg_part_type].anim_orient = forward_play_type;
				CSOL_SetSequence(m->model, LEG_PART, leg_anim);
			}
		}
		data->last_play_time = 0.0f;
		data->num = num;

		if((status & run_status_type) && data->idata[character_leg_part_type].anim_orient != o)
		{
			data->idata[character_leg_part_type].anim_orient = o;
		}
	}
	else
		return 0;
	return 1;
}

int Game_DeattachStatus(unsigned status, unsigned ret[character_all_part_type])
{
	if(!ret)
		return -1;
	int num = 0;
	unsigned s = status;
	unsigned ref = (~0) & 0xFF;
	unsigned r = s & ref;
	if(r)
	{
		ret[0] = r;
		return -1;
	}
	s = status & (~0xFF);
	ref = (((~0) >> 8) & (0xFF)) << 8;
	r = s & ref;
	if(r)
	{
		ret[character_leg_part_type] = r;
		num++;
	}
	ref = (((~0) >> 16) & (0xFF)) << 16;
	r = s & ref;
	if(r)
	{
		ret[character_body_part_type] = r;
		num++;
	}
	return num;
}

status_compare_result Game_CompareStatus(unsigned a, unsigned b)
{
	unsigned ads[character_all_part_type] = { 0 };
	unsigned bds[character_all_part_type] = { 0 };
	int an = Game_DeattachStatus(a, ads);
	int bn = Game_DeattachStatus(b, bds);

	if((an == -1 && bn == -1))
	{
		if(ads[0] != bds[0])
			return status_compare_one_different;
		else
			return status_compare_all_equals;
	}

	if(an == -1 || bn == -1)
		return status_compare_type_different;

	if(an != bn)
		return status_compare_num_different;

	unsigned r = 0;
	int i;
	for(i = 0; i < an; i++)
	{
		if(ads[i] != bds[i])
			r |= (1 << i);
	}
	return (status_compare_result)r;
}

void Game_RenderGameCharacterShadowVolume(const game_character *gamer, const Light_Source_s *light)
{
	const weapon *wp;

	if(!gamer || !light)
		return;

	wp = Game_CharacterCurrentWeapon((game_character *)gamer);

	if(gamer->model.source == lol_model_type)
	{
		if(!gamer->model.lol_character.model)
			return;
	}

	else if(gamer->model.source == netlizard_model_type)
	{
		if(!gamer->model.netlizard_character.model)
			return;

#if 0
		if(wp && wp->model && wp->model->tp_model)
		{
			glPushMatrix();
			{
				if(gamer->current_status & attack_status_type)
				{
					glTranslatef(wp->render_position[0], wp->render_position[1], wp->render_position[2]);
					glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
					glTranslatef(0.0, gamer->width, 0.0);
					glTranslatef(wp->model->position[0], wp->model->position[1], wp->model->position[2]);
					if((IS_NEAR_WEAPON(*wp)) || (IS_GRENADE_WEAPON(*wp)))
						glTranslatef(0.0, -90.0, 0.0);
				}
				else if(gamer->current_status == death_status_type)
				{
					glTranslatef(gamer->position[0], gamer->position[1], gamer->position[2]);
					glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
					glTranslatef(wp->model->position[0], wp->model->position[1], wp->model->position[2]);
				}
				else
				{
					if((IS_NEAR_WEAPON(*wp)) || (IS_GRENADE_WEAPON(*wp)))
					{
						glTranslatef(gamer->position[0], gamer->position[1], gamer->position[2] + gamer->full_height / 2);
						glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
						glRotatef(90.0, 1.0f, 0.0f, 0.0f);
						glTranslatef(-30.0, 0.0, 0.0);
						glTranslatef(0.0, 0.0, wp->model->position[2]);
					}
					else if((IS_LONG_WEAPON(*wp)) || (IS_LAUNCHER_WEAPON(*wp)))
					{
						glTranslatef(wp->render_position[0], wp->render_position[1], wp->render_position[2]);
						glRotatef(gamer->y_angle, 0.0f, 0.0f, 1.0f);
						glTranslatef(0.0, gamer->width, 0.0);
						glRotatef(90.0, 1.0f, 0.0f, 0.0f);
						glRotatef(90.0, 0.0f, 1.0f, 0.0f);
						glTranslatef(30.0, 0.0, 0.0);
						glTranslatef(0.0, 0.0, wp->model->position[2]);
					}
				}
				glRotatef(wp->model->tp_model->item_meshes[0].angle[0], 1.0f, 0.0f, 0.0f);
				glRotatef(wp->model->tp_model->item_meshes[0].angle[1], 0.0f, 0.0f, 1.0f);
				if(wp->model->scale != 1.0)
					glScalef(wp->model->scale, wp->model->scale, wp->model->scale);

				Shadow_RenderNETLizard3DMesh(&(wp->model->tp_model->item_meshes[0].item_mesh), NULL, 0, 0, lightpos);
			}
			glPopMatrix();
		}
#endif
		Shadow_RenderNETLizard3DAnimationModel(gamer->model.netlizard_character.model, gamer->animation.idata[0].anim, gamer->animation.idata[0].frame, gamer->position, 0, gamer->y_angle + gamer->model.netlizard_character.z_offset, light);
	}

	else if(gamer->model.source == csol_model_type)
	{
		if(!gamer->model.csol_character.model)
			return;
	}
	else
		return;
}
