#include "racing_game_viewer.h"
#include "gl_3d_main.h"
#include "nl_algo.h"
#include "gl_util.h"
#include "gl_object.h"
#include "nl_gl.h"
#include "nl_game.h"
#include "game_util.h"
#include "math3d/algo.h"
#include "game/character.h"
#include "netlizard/nl_util.h"
#include "action_signal_slot.h"
#include "game_std.h"
#include "game_music.h"
#include "game_setting.h"
#include "vkb.h"
#include "cross_hair.h"

#define PAGE_NAME "RacingGameViewer"

#define WHO_AM_I 0
#define GROUP_COUNT 2
#define CHARACTER_COUNT 4
#define LIGHTING_MOVE_UNIT 30.0
#define LIGHTING_SOURCE_DISTANCE 10000.0
#define LIGHTING_SOURCE_LENGTH 250.0

#define COLLISION_WIDTH 50 // 40 // 40 * 2
#define COLLISION_HEIGHT 180 // 190
#define FULL_COLLISION_HEIGHT 250 // 236

#define FOG_NEAR 3500.0
#define FOG_FAR 5000.0

#define FRUSTUM_NEAR 0.1
#define FRUSTUM_FAR 20000.0
#define FRUSTUM_WIDTH 360
#define FRUSTUM_HEIGHT 200

#define FOXY_MIN 9.0
#define FOXY_MAX 45.0
#define FOXY_ZOOM_IN_UNIT 150
#define FOXY_ZOOM_OUT_UNIT 75
#define TP_FOXY_MIN 30.0
#define FP_FOXY_ZOOM_IN_UNIT 120
#define FP_FOXY_ZOOM_OUT_UNIT 60
#define FREE_VIEW_ANGLE_UNIT 180

#define FP_FILE _KARIN_RESOURCE_DIR"resource/c%d.png"

typedef enum _lighting_move_type
{
	lighting_x_move_type = 0,
	lighting_y_move_type,
	lighting_total_move_type
} lighting_move_type;

extern char shared_str[DEBUG_STRING_MAX_LENGTH];

static GLfloat scene_scale = 100.0;
static person_mode p_mode = third_person_mode;
static unsigned lighting_move_state[lighting_total_move_type] = { 0 };
static float lighting_x_angle = 0.0;
static float lighting_y_angle = 0.0;
static GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0 };
static unsigned long long time = 0;
static vkb vkb_layer;
static game_character player;
static GLfloat frustum[6][4];
static game_name game;
static char *map_file = NULL;
static bool_t dbg = 0;
static mask_t view_free_reason = view_auto_free_type;
static bool_t is_lighting = 0;
static scene_2d bg;
static cross_hair fps_cross_hair;
static cross_hair tps_ray_cross_hair;
static GL_RE3D_Model *map_model = NULL;
static int level = -1;
static GLdouble foxy = 45.0;
static GLdouble frustum_far = FRUSTUM_FAR;
static GLuint frustum_width = FRUSTUM_WIDTH;
static GLuint frustum_height = FRUSTUM_HEIGHT;
static bool_t has_init = 0; 
static int last_key = Harmattan_Total_Key;
static int last_pressed = 0;

// setting
static bool_t god_mode = 0;
static bool_t open_vkb = 1;
static bool_t play_sound = 1;
static bool_t show_fps = 1;
static bool_t open_radar = 1;
static int tp_x_offset = 10;
static int tp_y_offset = 25;
static int tp_dis = 300;
static bool_t lighting_effect = 0;
static bool_t fog_effect = 0;
static bool_t tps_using_ray_crosshair = 0;

static void Game_RacingQuitViewer(void);
static void Game_RacingResetViewer(void);
static void Game_InitFunc(void);
static void Game_DrawFunc(void);
static void Game_FreeFunc(void);
static int Game_IdleFunc(void);
static void Game_ReshapeFunc(int w, int h);
static void Game_RacingUpdateLightingDirection(void);
static void Game_RacingRenderLightingSource(void);
static int Game_KeyFunc(int key, int a, int pressed, int x, int y);
static int Game_MouseFunc(int b, int p, int x, int y);
static int Game_ClickFunc(int b, int x, int y);
static int Game_MotionFunc(int b, int p, int x, int y, int dx, int dy);
static Main3DStoreFunction_f Game_StoreFunc = NULL;
static Main3DRestoreFunction_f Game_RestoreFunc = NULL;

static void Game_InitGlobalLighting(void);
static void Game_InitPlayerLighting(void);

static void Game_RacingUpdateGLTransform(game_character *gamer);
static int Game_RacingUpdatePlayerAI(Game_Action a, int p);
static int Game_RacingInitGame(void);
static void Game_RacingHandlePlayerAI(game_character *gamer, long long time);
static int Game_ActionEvent(int b, int a, int p);
static void Game_GetSetting(void);

void Game_InitPlayerLighting(void)
{
#ifndef _HARMATTAN_OPENGLES2
	GLfloat ambient_light[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};
	GLfloat diffuse_light[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};
	GLfloat specular_light[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);

	GLfloat spot_directory[] = {
		0.0, 0.0, -1.0
	};
	GLfloat spot_cutoff = 10.0f;
	GLfloat spot_exponent = 64.0f;
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_directory);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exponent);

	GLfloat pos[] = {0.0, 0.0, -45.0, 1.0};
	glLightfv(GL_LIGHT1, GL_POSITION, pos);

	//oglEnable(GL_LIGHT1);
#endif
}

void Game_InitGlobalLighting(void)
{
#ifndef _HARMATTAN_OPENGLES2
	vector3_t dir = {light_position[0], light_position[1], light_position[2]};
	Vector3_Normalize(&dir);
	light_position[0] = dir.x;
	light_position[1] = dir.y;
	light_position[2] = dir.z;
	Algo_GetNormalAngle(&dir, &lighting_y_angle, &lighting_x_angle);
	GLfloat ambient_light[] = {
		0.4f, 0.4f, 0.4f, 1.0f
	};
	GLfloat diffuse_light[] = {
		0.4f, 0.4f, 0.4f, 1.0f
	};
	GLfloat specular_light[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

	GLfloat material_specular[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};
	GLfloat material_ambient_and_diffuse[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};
	GLfloat material_shiness = 10.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material_ambient_and_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_shiness);

	GLfloat global_ambient_light[] = {
		0.2f, 0.2f, 0.2f, 1.0f
	};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient_light);
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	oglEnable(GL_LIGHT0);
#endif
}

int Game_RacingViewerInitMain(const char *g, const char *d, const char *src, unsigned int lvl)
{
	if(has_init)
		return 0;
	if(!g)
		return 0;
	if(strcasecmp(g, "re3d") != 0)
		return 0;
	char *dir = NULL;
	if(d)
		dir = strdup(d);
	else
		dir = strdup(".");
	game = nl_racing_evolution_3d;
	if(src)
	{
		map_file = strdup(src);
	}
	else
	{
		size_t len = strlen(dir) + 1 + 6 + 1 + 4 + 1;
		map_file = NEW_II(char, len);
		sprintf(map_file, "%s/"RE3D_LEVEL_FILE_SUBFIX, dir, lvl);
	}
	level = lvl;
	//nlSetResourcePath(game, dir);
	const void *slot = SignalSlot_GetAction(LOADING_PROGRESS_CALLBACK);
	void__func__int_int_constcharptr loading_progress_func = NULL;
	if(slot)
		loading_progress_func = (void__func__int_int_constcharptr)slot;
	if(loading_progress_func)
		loading_progress_func(0, 10, "Get game map file");
	free(dir);
	return Game_RacingInitGame();
}

void Game_RacingViewerRegisterFunction(void)
{
	glk_function func;

	func = REGISTER_RENDER_FUNCTION(Game);
	Main3D_InitRenderPage(PAGE_NAME, &func);

	const void *slot = SignalSlot_GetAction(PLAY_LEVEL_MUSIC);
	if(slot)
	{
		((void__func__int_int)slot)(game, level);
	}
	if(has_init)
	{
		const void *slot = SignalSlot_GetAction(SET_GAME_STATE);
		if(slot)
			((void__func__int)slot)(game_in_game_state);
	}
}

int Game_RacingInitGame(void)
{
	if(has_init)
		return 0;

	const void *slot = SignalSlot_GetAction(LOADING_PROGRESS_CALLBACK);
	void__func__int_int_constcharptr loading_progress_func = NULL;
	if(slot)
		loading_progress_func = (void__func__int_int_constcharptr)slot;
	if(loading_progress_func)
		loading_progress_func(0, 20, "Init GL State");
	//move_unit_3d = 800;
	turn_unit_3d = FREE_VIEW_ANGLE_UNIT;

	GLfloat bg_color[] = {0.2, 0.2, 0.2, 1.0};
	OpenGL_InitFog(GL_EXP, FOG_NEAR, FOG_FAR, 0.0002f, bg_color);
#ifndef _HARMATTAN_OPENGLES2
	Game_InitGlobalLighting();
	Game_InitPlayerLighting();
#endif

	printf("Read NETLizard map file: %s\n", map_file);
	if(loading_progress_func)
		loading_progress_func(0, 40, "Reading map file");
	map_model = NETLizard_ReadGLRE3DModelFile(map_file);
	if(map_model)
	{
		if(loading_progress_func)
			loading_progress_func(0, 60, "Read map model successful");
		bg.tex = map_model->bg_tex;
	}
	else
	{
		if(loading_progress_func)
			loading_progress_func(1, 100, "Read map model fail");
		return 0;
	}
	if(loading_progress_func)
		loading_progress_func(0, 70, "Init game setting");
	Game_GetSetting();
	/*
		 x_t_3d = -map_model->start_pos[0];
		 y_t_3d = -map_model->start_pos[2];
		 z_t_3d = map_model->start_pos[1];
		 y_r_3d = Algo_FormatAngle(map_model->start_angle[1] - 180.0);
	//x_r_3d = map_model->start_angle[0];
	*/

	if(loading_progress_func)
		loading_progress_func(0, 80, "Get game resource");

	new_scene_2d(&bg, 0.0f, 0.0f, width, height, 1.0, left_bottom_anchor_type, Color_GetColor(white_color, 0.0), NULL);

	new_normal_cross_hair(&fps_cross_hair, cross_type, X11_COLOR(white), 20.0, 2.0, 20.0);
	new_ray_cross_hair(&tps_ray_cross_hair, ray_type, Color_GetColor(red_color, 0.8), 2.0, 20, 200);
	new_vkb(&vkb_layer, 0, 0, 0, HARMATTAN_FULL_WIDTH, HARMATTAN_FULL_HEIGHT);

	if(loading_progress_func)
		loading_progress_func(0, 90, "Init game character");
	new_game_character(&player, lucia, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "karin", 0, NULL, 0);
	time = Game_GetGameTime();
	player.ai.type = ai_player_type;
	player.ai.time = time;

	frustum_far = FRUSTUM_FAR;
	if(loading_progress_func)
		loading_progress_func(0, 100, "Start game");
	is_cross = 1;
	has_init = 1;
	return 1;
}

void Game_DrawFunc(void)
{
	if(!has_init)
		return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int *scenes = NULL;
	unsigned int count = 0;

	// 渲染2D背景
	if(map_model->bg_tex)
	{
		OpenGL_Render2D(0.0, width, 0.0, height);
		{
			UI_RenderScene2D(&bg);
		}
	}

#ifndef _HARMATTAN_OPENGLES2
	if(lighting_effect || is_lighting)
		oglEnable(GL_LIGHTING);
#endif
	if(fog_effect)
		oglEnable(GL_FOG);
#ifndef _HARMATTAN_OPENGLES2
	if(is_lighting)
		oglEnable(GL_LIGHT1);
#endif
	OpenGL_Render3D(foxy, width, height, FRUSTUM_NEAR, frustum_far);
	{
		// 渲染地图场景
		glPushMatrix();
		{
			Main3D_ModelViewTransform(p_mode, -25.0, -15.0, 120.0, 0);
			if(lighting_effect)
			{
				oglEnable(GL_LIGHT0);
				glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			}
			else
				oglDisable(GL_LIGHT0);

			if(1)
			{
				OpenGL_ExtractFrustum(frustum);
				scenes = Algo_GetRE3DMapRenderScenes(map_model, &count, frustum);
			}

			glPushMatrix();
			{
				glRotatef(90.0, 1.0, 0.0, 0.0);
				glScalef(scene_scale, scene_scale, scene_scale);
				if(scenes)
				{
					NETLizard_RenderGLRE3DModelScene(map_model, scenes, count);
				}
				else
					NETLizard_RenderGLRE3DModel(map_model);
			}
			glPopMatrix();
			// 渲染角色第三人称视角
			if(p_mode == third_person_mode)
				Game_RenderGameCharacter(&player);

			// 渲染圆点瞄准器
			if(lighting_effect)
			{
				Game_RacingRenderLightingSource();
			}
		}
		glPopMatrix();
	}

	if(fog_effect)
		oglDisable(GL_FOG);
#ifndef _HARMATTAN_OPENGLES2
	if(is_lighting)
		oglDisable(GL_LIGHT1);
#endif

#ifndef _HARMATTAN_OPENGLES2
	if(lighting_effect || is_lighting)
		oglDisable(GL_LIGHTING);
#endif
	OpenGL_Render2D(0.0, width, 0.0, height);
	glPushMatrix();
	{
		fps_cross_hair.normal.pos[0] = width / 2;
		fps_cross_hair.normal.pos[1] = height / 2;
		fps_cross_hair.normal.pos[2] = 0.0;
		UI_RenderCrossHair(&fps_cross_hair);
	}
	glPopMatrix();

	if(open_vkb)
	{
		glPushMatrix();
		{
			glTranslatef(0.0, 0.0, 0.5);
			UI_RenderVKB(&vkb_layer);
		}
		glPopMatrix();
	}
	if(show_fps)
	{
		char *f = itostr(fps);
		char *str = NEW_II(char, 7 + strlen(f));
		sprintf(str, "FPS : %s", f);
		Font_RenderString(&fnt, 4, height - fnt.height, 0.0, 1.0, 0.0, 1.0, str);
		free(f);
		free(str);
	}

	// 渲染调试文本
	if(dbg)
	{
		char str[100];
		memset(str, '\0', 100 * sizeof(char));
		Font_RenderString(&fnt, 4, height - 8 * fnt.height, 0.0, 1.0, 0.0, 1.0, map_file);
		sprintf(str, "Pos->(%.2f, %.2f, %.2f)", player.position[0], player.position[1], player.position[2]);
		Font_RenderString(&fnt, 4, height - 9 * fnt.height, 0.0, 1.0, 0.0, 1.0, str);
		sprintf(str, "Ang->(%.0f, %.0f) Dir->(%.2f, %.2f, %.2f)", player.x_angle, player.y_angle, player.direction[0], player.direction[1], player.direction[2]);
		Font_RenderString(&fnt, 4, height - 10 * fnt.height, 0.0, 1.0, 0.0, 1.0, str);
		sprintf(str, "Scene->(%d / %d) Item->%d", player.scene, map_model->count, player.collision_item);
		Font_RenderString(&fnt, 4, height - 11 * fnt.height, 0.0, 1.0, 0.0, 1.0, str);
		sprintf(str, "y->%d x->%d dis->%d", tp_y_offset, tp_x_offset, tp_dis);
		Font_RenderString(&fnt, 4, height - 12 * fnt.height, 0.0, 1.0, 0.0, 1.0, str);
		if(last_key != Harmattan_Total_Key)
		{
			sprintf(str, "%s - %s", Key_Infos[last_key].symbol, last_pressed ? "pressed" : "released");
			Font_RenderString(&fnt, 4, height - 13 * fnt.height, 0.0, 1.0, 0.0, 1.0, str);
		}
		if(*shared_str)
			Font_RenderString(&fnt, 4, height - 14 * fnt.height, 0.0, 1.0, 0.0, 1.0, shared_str);
	}
	if(scenes)
		free(scenes);
}

void Game_FreeFunc(void)
{
	if(!has_init)
		return;
	FREE_PTR(map_file)
		if(map_model)
		{
			delete_GL_RE3D_Model(map_model);
			free(map_model);
			map_model = NULL;
		}
	bg.tex = NULL;
	delete_scene_2d(&bg);

	delete_game_character(&player);

	delete_vkb(&vkb_layer);
	Game_RacingResetViewer();
#ifndef _HARMATTAN_OPENGLES2
	oglDisable(GL_LIGHTING);
#endif
	oglDisable(GL_FOG);
	has_init = 0;

	NL_PAGE_DESTROY_DEBUG(PAGE_NAME)
}

// 指定角色，来更新视觉坐标
void Game_RacingUpdateGLTransform(game_character *gamer)
{
	if(!has_init)
		return;
	if(!gamer)
		return;
	x_t_3d = -gamer->position[0];
	y_t_3d = -gamer->position[2] - gamer->height;
	z_t_3d = gamer->position[1];
	x_r_3d = gamer->x_angle;
	y_r_3d = Algo_FormatAngle(-gamer->y_angle - 180.0);

	if(p_mode == third_person_mode)
	{
		gl_vector3_t third = {0.0, 0.0, 0.0};
		//if(Algo_UpdateThirdPersonPosition(&third.x, &third.y, &third.z, x_t_3d, y_t_3d, z_t_3d, x_r_3d, y_r_3d, -27.0, 15.0, 180.0, gamer->scene, gamer->scene_collision_result))
		float rxr = 0.0;
		float ryr = 0.0;
		if(view_free_reason & view_game_free_type)
		{
			view_free_reason = view_auto_free_type;
			view_free_mode = GL_FALSE;
		}
		if(view_free_mode)
		{
			float r = turn_unit_3d * delta_time;
			if(action_state[FreeViewTurnLeft_Action] && action_state[FreeViewTurnRight_Action] == 0)
			{
				view_y_angle = Algo_FormatAngle(view_y_angle + r);
				/*
					 if(Algo_FormatAngle(view_y_angle - gamer->y_angle) > 180.0)
					 view_y_angle = Algo_FormatAngle(gamer->y_angle + 180.0);
					 */
			}
			else if(action_state[FreeViewTurnLeft_Action] == 0 && action_state[FreeViewTurnRight_Action])
			{
				view_y_angle = Algo_FormatAngle(view_y_angle - r);
				/*
					 if(Algo_FormatAngle(view_y_angle - gamer->y_angle) < 180.0)
					 view_y_angle = Algo_FormatAngle(gamer->y_angle - 180.0);
					 */
			}
			if(action_state[FreeViewTurnUp_Action] && action_state[FreeViewTurnDown_Action] == 0)
			{
				view_x_angle = Algo_FormatAngle(view_x_angle - r);
				if(Algo_FormatAngle(view_x_angle + - 180.0f) < 90.0f)
					view_x_angle = 270.0f;
			}
			else if(action_state[FreeViewTurnUp_Action] == 0 && action_state[FreeViewTurnDown_Action])
			{
				view_x_angle = Algo_FormatAngle(view_x_angle + r);
				if(Algo_FormatAngle(view_x_angle - 180.0f) > 270.0f)
					view_x_angle = 90.0f;
			}
		}
		/*
			 else
			 view_y_angle = gamer->y_angle;
			 */

		if(Algo_ComputeThirdPersonPosition(NULL, gamer, tp_y_offset, tp_x_offset, tp_dis, is_cross, view_free_mode, view_y_angle, view_x_angle, &third, &ryr, &rxr))
		{
			tp_x_t_3d = third.x;
			tp_y_t_3d = third.y;
			tp_z_t_3d = third.z;
			tp_y_r_3d = ryr;
			tp_x_r_3d = rxr;
			/*
				 wp->position[0] = -third.x;
				 wp->position[1] = third.z;
				 wp->position[2] = -third.y;
				 wp->x_angle = Algo_FormatAngle(gamer->x_angle + 15);
				 wp->y_angle = Algo_FormatAngle(gamer->y_angle + 27);
				 */
		}
	}
}

// 接收按键操作动作来更新动作
int Game_RacingUpdatePlayerAI(Game_Action a, int p)
{
	if(!has_init)
		return 0;
	if(a == Total_Action)
		return 0;
	int r = 1;
	switch(a)
	{
		case Forward_Action:
			if((!p && (player.ai.action & aiaction_moveforward_type)) || (p && (player.ai.action & aiaction_moveforward_type) == 0))
				player.ai.action ^= aiaction_moveforward_type;
			break;
		case Backward_Action:
			if((!p && (player.ai.action & aiaction_movebackward_type)) || (p && (player.ai.action & aiaction_movebackward_type) == 0))
				player.ai.action ^= aiaction_movebackward_type;
			break;
		case MoveLeft_Action:
			if((!p && (player.ai.action & aiaction_moveleft_type)) || (p && (player.ai.action & aiaction_moveleft_type) == 0))
				player.ai.action ^= aiaction_moveleft_type;
			break;
		case MoveRight_Action:
			if((!p && (player.ai.action & aiaction_moveright_type)) || (p && (player.ai.action & aiaction_moveright_type) == 0))
				player.ai.action ^= aiaction_moveright_type;
			break;
		case Jump_Action:
		case MoveUp_Action:
			if((!p && (player.ai.action & aiaction_moveup_type)) || (p && (player.ai.action & aiaction_moveup_type) == 0))
				player.ai.action ^= aiaction_moveup_type;
			break;
		case Crouch_Action:
		case MoveDown_Action:
			if((!p && (player.ai.action & aiaction_movedown_type)) || (p && (player.ai.action & aiaction_movedown_type) == 0))
				player.ai.action ^= aiaction_movedown_type;
			break;
		case PrevWeapon_Action:
		case TurnLeft_Action:
			if((!p && (player.ai.action & aiaction_turnleft_type)) || (p && (player.ai.action & aiaction_turnleft_type) == 0))
				player.ai.action ^= aiaction_turnleft_type;
			break;
		case NextWeapon_Action:
		case TurnRight_Action:
			if((!p && (player.ai.action & aiaction_turnright_type)) || (p && (player.ai.action & aiaction_turnright_type) == 0))
				player.ai.action ^= aiaction_turnright_type;
			break;
		case TurnUp_Action:
			if((!p && (player.ai.action & aiaction_turnup_type)) || (p && (player.ai.action & aiaction_turnup_type) == 0))
				player.ai.action ^= aiaction_turnup_type;
			break;
		case TurnDown_Action:
			if((!p && (player.ai.action & aiaction_turndown_type)) || (p && (player.ai.action & aiaction_turndown_type) == 0))
				player.ai.action ^= aiaction_turndown_type;
			break;
		case Attack_Action:
			break;
		case Reload_Action:
			if(p)
			{
				player.ai.action |= aiaction_reload_type;
			}
			break;
		//case Jump_Action:
			if(p)
			{
				if(player.z_moving.state == no_z_type)
				{
					player.z_moving.state = z_jumping_type;
					player.z_moving.start_z = player.position[2];
					player.z_moving.start_time = time;
					player.z_moving.jump_speed = -player.z_jump_speed;
					player.z_moving.speed = player.z_moving.jump_speed;
				}
			}
			break;
		case FreeViewMode_Action:
			if(view_free_reason & view_game_free_type)
				break;
			view_free_mode = p ? GL_TRUE : GL_FALSE;
			view_free_reason = p ? view_force_free_type : view_auto_free_type;
			if(!view_free_mode)
			{
				view_x_angle = 0.0f;
				view_y_angle = 0.0f;
			}
			else
			{
				view_x_angle = player.x_angle;
				view_y_angle = player.y_angle;
			}
			break;
		case FreeViewTurnLeft_Action:
		case FreeViewTurnRight_Action:
		case FreeViewTurnUp_Action:
		case FreeViewTurnDown_Action:
			if(view_free_reason != view_auto_free_type)
				break;
			if(!view_free_mode)
			{
				if(action_state[FreeViewTurnUp_Action] || action_state[FreeViewTurnDown_Action] || action_state[FreeViewTurnLeft_Action] || action_state[FreeViewTurnRight_Action])
					view_free_mode = GL_TRUE;
				else
					break;
			}
			else
			{
				if(action_state[FreeViewTurnUp_Action] == 0 && action_state[FreeViewTurnDown_Action] == 0 && action_state[FreeViewTurnLeft_Action] == 0 && action_state[FreeViewTurnRight_Action] == 0)
					view_free_mode = GL_FALSE;
				else
					break;
			}
			if(!view_free_mode)
			{
				view_x_angle = 0.0f;
				view_y_angle = 0.0f;
			}
			else
			{
				view_x_angle = player.x_angle;
				view_y_angle = player.y_angle;
			}
			break;
		default:
			r = 0;
			break;
	}
	return r;
}

int Game_IdleFunc(void)
{
	if(!has_init)
		return 0;
	time = Game_GetGameTime();
	unsigned up_light = 0;
	if(lighting_move_state[lighting_x_move_type])
	{
		lighting_x_angle = Algo_FormatAngle(lighting_x_angle + LIGHTING_MOVE_UNIT * delta_time);
		up_light = 1;
	}
	else
	{
		lighting_x_angle = Algo_FormatAngle(lighting_x_angle + LIGHTING_MOVE_UNIT / 2.0 * delta_time);
		up_light = 1;
	}
	if(lighting_move_state[lighting_y_move_type])
	{
		lighting_y_angle = Algo_FormatAngle(lighting_y_angle + LIGHTING_MOVE_UNIT * delta_time);
		up_light = 1;
	}
	if(up_light)
	{
		Game_RacingUpdateLightingDirection();
	}

	Game_RacingHandlePlayerAI(&player, time);
	Game_CharacterPlayAnimation(&player, time, fps, delta_time);
	player.ai.time = time;
	Game_RacingUpdateGLTransform(&player);

	return 1;
}

int Game_KeyFunc(int key, int a, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	if(dbg)
	{
		last_key = key;
		last_pressed = pressed;
	}
	int res = 0;
	res = Game_ActionEvent(key, a, pressed);

	return res;
}

void Game_ReshapeFunc(int w, int h)
{
	if(!has_init)
		return;
#ifdef _HARMATTAN_OPENGL
	glViewport( (w - viewport_width) / 2, (h - viewport_height) / 2, viewport_width, viewport_height);
#else
	glViewport(0, 0, w, h);
#endif
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	UI_ResizeScene2D(&bg, w, h);
}

void Game_InitFunc(void)
{
	GLfloat bg_color[] = {0.1, 0.1, 0.1, 0.4};
	glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
	glShadeModel(GL_SMOOTH);
	oglEnable(GL_TEXTURE_2D);
	oglEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);

	glCullFace(GL_BACK);
	oglEnable(GL_CULL_FACE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	oglEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	viewport_width = frustum_width;
	viewport_height = frustum_height;

	x_a_3d = -90;
}

int Game_MouseFunc(int b, int p, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(open_vkb)
		return UI_VKBMouseEvent(&vkb_layer, b, p ,x, gl_y, Game_ActionEvent);
	else
		return 0;
}

int Game_ClickFunc(int b, int x, int y)
{
	if(!has_init)
		return 0;
	//int gl_y = height - y;
	return 0;
}

int Game_MotionFunc(int b, int p, int x, int y, int dx, int dy)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(open_vkb)
		return UI_VKBMouseMotionEvent(&vkb_layer, b, p ,x, gl_y, dx, -dy, Game_ActionEvent);
	else
		return 0;
}

void Game_RacingResetViewer(void)
{
	last_key = Harmattan_Total_Key;
	last_pressed = 0;
	turn_unit_3d = FREE_VIEW_ANGLE_UNIT;
	view_free_mode = GL_FALSE;
	view_y_angle = 0.0;
	view_x_angle = 0.0;
	//game_name game;
	//map_file = NULL;
	dbg = 0;
	is_lighting = 0;
	view_free_reason = view_auto_free_type;
	//map_model = NULL;
	level = -1;

	frustum_far = FRUSTUM_FAR;
	frustum_width = FRUSTUM_WIDTH;
	frustum_height = FRUSTUM_HEIGHT;

	god_mode = 0;
	open_vkb = 1;
	play_sound = 1;
	show_fps = 1;
	open_radar = 1;
	tp_x_offset = 10;
	tp_y_offset = 25;
	tp_dis = 300;
	lighting_effect = 0;
	fog_effect = 0;
	tps_using_ray_crosshair = 0;

	lighting_move_state[lighting_x_move_type] = 0;
	lighting_move_state[lighting_y_move_type] = 0;
}

int Game_ActionEvent(int key, int a, int pressed)
{
	if(!has_init)
		return 0;
	int res = 0;
	if(a != Total_Action)
	{
		action_state[a] = pressed ? 1 : 0;
		res = Game_RacingUpdatePlayerAI(a, pressed);
		switch(a)
		{
			case ViewCenter_Action:
				if(pressed)
				{
					player.x_angle = 0.0;
				}
				break;
			case Quit_Action:
				if(pressed)
				{
					Game_RacingQuitViewer();
					res |= 1;
				}
				break;
			case ConsoleMode_Action:
				if(pressed)
				{
					dbg ^= 1;
					res = 1;
				}
				break;
			case OpenLight_Action:
				if(pressed)
				{
					is_lighting ^= 1;
					res = 1;
				}
				break;
			case OpenScore_Action:
				if(pressed)
				{
					lighting_effect ^= 1;
					res = 1;
				}
				break;
			//case PrevWeapon_Action:
				break;
			//case NextWeapon_Action:
				break;
			case ZoomOut_Action:
				break;
			case ZoomIn_Action:
				break;
			case PersonMode_Action:
				if(pressed)
				{
					p_mode ^= third_person_mode;
					res = 1;
				}
				break;
			case OperateGo_Action:
				lighting_move_state[lighting_x_move_type] = pressed;
				break;
			case OperateBack_Action:
				lighting_move_state[lighting_y_move_type] = pressed;
				break;
			case OperateStand_Action:
				break;
			case OpenRadar_Action:
				if(pressed)
				{
					fog_effect ^= 1;
					res = 1;
				}
				break;
			default:
				break;
		}
	}

	if(key < Harmattan_Other_Key)
	{
		switch(key)
		{
			case Harmattan_K_parenleft:
				lighting_move_state[lighting_x_move_type] = pressed;
				break;
			case Harmattan_K_parenright:
				lighting_move_state[lighting_y_move_type] = pressed;
				break;
			case Harmattan_K_Control_R:
			case Harmattan_K_Control_L:
				if(pressed)
				{
					is_cross ^= 1;
					res = 1;
				}
				break;
			case Harmattan_K_less:
				break;
			case Harmattan_K_at:
				break;
			case Harmattan_K_question:
				break;
			case Harmattan_K_greater:
				break;
			case Harmattan_K_underscore:
				break;
			case Harmattan_K_5:
				if(pressed)
				{
					tp_y_offset--;
					res = 1;
				}
				break;
			case Harmattan_K_6:
				if(pressed)
				{
					tp_y_offset++;
					res = 1;
				}
				break;
			case Harmattan_K_7:
				if(pressed)
				{
					tp_x_offset--;
					res = 1;
				}
				break;
			case Harmattan_K_8:
				if(pressed)
				{
					tp_x_offset++;
					res = 1;
				}
				break;
			case Harmattan_K_9:
				if(pressed)
				{
					tp_dis -= 10;
					res = 1;
				}
				break;
			case Harmattan_K_0:
				if(pressed)
				{
					tp_dis += 10;
					res = 1;
				}
				break;
			case Harmattan_K_4:
				if(pressed)
				{
					god_mode ^= 1;
					res = 1;
				}
				break;
			default:
				break;
		}
	}
	return res;
}

void Game_GetSetting(void)
{
	char b = 0;
	b = 0;
	if(Setting_GetSettingBoolean(GOD_MODE_SETTING, &b))
		god_mode = b;
	b = 0;
	if(Setting_GetSettingBoolean(OPEN_VKB_SETTING, &b))
		open_vkb = b;
	b = 0;
	if(Setting_GetSettingBoolean(OPEN_GAME_SOUND_SETTING, &b))
		play_sound = b;
	b = 0;
	if(Setting_GetSettingBoolean(SHOW_FPS_SETTING, &b))
		show_fps = b;
	b = 0;
	if(Setting_GetSettingBoolean(OPEN_RADAR_SETTING, &b))
		open_radar = b;
	int i = 0;
	if(Setting_GetSettingInteger(THIRD_PERSON_VIEW_X_OFFSET_SETTING, &i))
		tp_x_offset = i;
	i = 0;
	if(Setting_GetSettingInteger(THIRD_PERSON_VIEW_Y_OFFSET_SETTING, &i))
		tp_y_offset = i;
	i = 0;
	if(Setting_GetSettingInteger(THIRD_PERSON_VIEW_DISTANCE_SETTING, &i))
		tp_dis = i;
	b = 0;
	if(Setting_GetSettingBoolean(LIGHTING_EFFECT_SETTING, &b))
		lighting_effect = b;
	b = 0;
	if(Setting_GetSettingBoolean(FOG_EFFECT_SETTING, &b))
		fog_effect = b;
	b = 0;
	if(Setting_GetSettingBoolean(THIRD_PERSON_VIEW_CROSSHAIR_SETTING, &b))
		tps_using_ray_crosshair = b;
}

void Game_RacingUpdateLightingDirection(void)
{
	nl_vector3_t dir = Algo_ComputeDirection(lighting_y_angle, lighting_x_angle);
	light_position[0] = dir.x;
	light_position[1] = dir.y;
	light_position[2] = dir.z;
}

void Game_RacingRenderLightingSource(void)
{
	vector3_t dir = {
		light_position[0],
		light_position[1],
		light_position[2]
	};
	dir = Vector3_Scale(&dir, frustum_far);
	const GLfloat length[3] = {
		LIGHTING_SOURCE_LENGTH, LIGHTING_SOURCE_LENGTH, LIGHTING_SOURCE_LENGTH,
	};
	glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_CURRENT_BIT);
	{
		//glDisable(GL_DEPTH_TEST);
		//glDepthMask(GL_FALSE);
		glPushMatrix();
		{
			glTranslatef(dir.x, dir.y, dir.z);
			oglColor4f(1.0, 0.0, 0.0, 1.0);
			OpenGL_CubeSimple(length);
		}
		glPopMatrix();
	}
	glPopAttrib();
}

void Game_RacingHandlePlayerAI(game_character *gamer, long long time)
{
	if(!gamer)
		return;
	if(gamer->ai.type != ai_player_type)
		return;
	// myself gamer model
	// get position and angle
	double per = (double)(time - gamer->ai.time) / 1000.0;
	float turn_unit = gamer->turn_unit * per;
	float move_unit = gamer->move_unit * per;

	nl_vector3_t ori_v = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};
	float oxr = gamer->x_angle;
	float oyr = gamer->y_angle;

	orientation_type o = center_orientation_type;
	position_type p = center_position_type;
	if(gamer->ai.action & aiaction_turnup_type)
		o |= up_orientation_type;
	if(gamer->ai.action & aiaction_turndown_type)
		o |= down_orientation_type;
	if(gamer->ai.action & aiaction_turnleft_type)
		o |= left_orientation_type;
	if(gamer->ai.action & aiaction_turnright_type)
		o |= right_orientation_type;

	if(gamer->ai.action & aiaction_moveforward_type)
		p |= forward_position_type;
	if(gamer->ai.action & aiaction_movebackward_type)
		p |= backward_position_type;
	if(gamer->ai.action & aiaction_moveleft_type)
		p |= left_position_type;
	if(gamer->ai.action & aiaction_moveright_type)
		p |= right_position_type;
	if(is_cross)
	{
		if(gamer->ai.action & aiaction_moveup_type)
			p |= up_position_type;
		if(gamer->ai.action & aiaction_movedown_type)
			p |= down_position_type;
	}

	// get return var
	float ryr = 0.0;
	float rxr = 0.0;
	nl_vector3_t rv = ori_v;

	Algo_TransformPositionAndAngle(p, &ori_v, move_unit, &rv, o, oxr, oyr, turn_unit, &rxr, &ryr, is_cross);

	if(o != center_orientation_type)
	{
		gamer->y_angle = ryr;
		gamer->x_angle = rxr;
	}

	if(1 || is_cross)
	{
		gamer->position[0] = rv.x;
		gamer->position[1] = rv.y;
		gamer->position[2] = rv.z - gamer->height;
		if(gamer->z_moving.state != no_z_type)
		{
			gamer->z_moving.speed = 0.0;
			gamer->z_moving.state = no_z_type;
		}
	}
	if(gamer->z_moving.state != no_z_type && (gamer->ai.action & aiaction_jump_type) == 0)
		gamer->ai.action |= aiaction_jump_type;
	else if(gamer->z_moving.state == no_z_type && gamer->ai.action & aiaction_jump_type)
		gamer->ai.action ^= aiaction_jump_type;
	Game_UpdateCharacterPositionAndDirection(gamer, gamer->position[0], gamer->position[1], gamer->position[2], gamer->x_angle, gamer->y_angle, 0);
}

void Game_RacingQuitViewer(void)
{
	const void *slot = SignalSlot_GetAction(INIT_MAIN_MENU);
	if(slot)
		((void__func__void)slot)();
}
