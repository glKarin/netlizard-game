#include "game_viewer.h"
#include "gl_3d_main.h"
#include "nl_algo.h"
#include "gl_util.h"
#include "nl_gl.h"
#include "game_util.h"
#include "game_event.h"
#include "math3d/algo.h"
#include "game/character.h"
#include "netlizard/nl_util.h"
#include "nl_game.h"
#include "game_mode.h"
#include "game_menu.h"
#include "action_signal_slot.h"
#include "particle.h"
#include "game_std.h"
#include "character_status_bar.h"
#include "first_person.h"
#include "game_music.h"
#include "game_sound.h"
#include "game_over.h"
#include "game_setting.h"
#include "score_table.h"
#include "vkb.h"
#include "cross_hair.h"
#include "radar.h"
#include "reloading_progress_bar.h"

#define WHO_AM_I 0
#define GROUP_COUNT 2
#define CHARACTER_COUNT 4

#define COLLISION_WIDTH 50 // 40 // 40 * 2
#define COLLISION_HEIGHT 180 // 190
#define FULL_COLLISION_HEIGHT 250 // 236
#define CIRCLE_WIDTH 200.0

#define FOG_NEAR 3500.0
#define FOG_FAR 5000.0

#define FRUSTUM_NEAR 0.1
#define FRUSTUM_FAR 4000.0
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
#define EVENT_FILE _KARIN_RESOURCE_DIR"resource/lvl.event"

typedef enum _zoom_type
{
	no_zoom_type = 0,
	third_person_zoom_type,
	sniper_zoom_type
} zoom_type;

typedef struct _zoom
{
	zoom_type type;
	int zoom_state;
	double min_foxy;
	double max_foxy;
	double foxy;
	double zoom_out_unit;
	double zoom_in_unit;
	int zoom_auto;
} zoom;

static zoom zm = {no_zoom_type, 0, FOXY_MAX, FOXY_MAX, FOXY_MAX, 0, 0, 0};
static int my_character_index = WHO_AM_I;
static vkb vkb_layer;
static particle_spirit spirit;
static glk_function internal_menu;
static glk_function game_over_surface;
static game_character *player = NULL;
static death_game_mode game_mode;
static GLfloat frustum[6][4];
static game_name game;
static char *map_file = NULL;
static bool_t dbg = 0;
static mask_t view_free_reason = view_auto_free_type;
static bool_t is_lighting = 0;
static scene_2d bg;
static first_person fp;
static cross_hair opticalsight;
static cross_hair fps_cross_hair;
static cross_hair tps_ray_cross_hair;
static radar rad;
static GL_NETLizard_3D_Model *map_model = NULL;
static int level = -1;
static character_status_bar status_bar;
static reloading_progress_bar reloading_bar;
static score_table score_tb;
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

static void Game_ResetViewer(void);
static void Game_ViewerInitFunc(void);
static void Game_ViewerDrawFunc(void);
static void Game_ViewerFreeFunc(void);
static int Game_ViewerIdleEventFunc(void);
static void Game_ViewerReshapeFunc(int w, int h);
static int Game_ViewerKeyFunc(int key, int a, int pressed, int x, int y);
static int Game_ViewerMouseEventFunc(int b, int p, int x, int y);
static int Game_ViewerMouseClickEventFunc(int b, int x, int y);
static int Game_ViewerMouseMotionEventFunc(int b, int p, int x, int y, int dx, int dy);
static void Game_UpdateFPPosition(const game_character *c);
static void Game_ViewerInitSimpleLight(void);
static void Game_UpdateZoomProgress(void);

static void Game_UpdateGLTransform(game_character *gamer);
static int Game_UpdatePlayerAI(Game_Action a, int p);
static void Game_UpdateRadar(const game_character *gamer, const game_character characters[], int start, int character_count, radar *r);
static int Game_InitGame(void);
static void Game_PauseGameAndOpenMenu(void);
static void Game_RenderGameParticle(unsigned int index, const void *data);
static void Game_PlayGameSound(unsigned int index, const void *data);
static int Game_ViewerActionEvent(int b, int a, int p);
static void Game_ViewerGetSetting(void);
static void Game_GameOver(void);

void Game_ViewerInitSimpleLight(void)
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
	GLfloat light_position[] = {
		0.0f, 0.0f, 1.0f, 1.0
	};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat spot_directory[] = {
		0.0, 0.0, -1.0
	};
	GLfloat spot_cutoff = 22.5f;
	GLfloat spot_exponent = 2.0f;
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_directory);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);

	GLfloat material_specular[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};
	GLfloat material_ambient_and_diffuse[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};
	GLfloat material_shiness = 0.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_ambient_and_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material_shiness);

	GLfloat global_ambient_light[] = {
		0.2f, 0.2f, 0.2f, 1.0f
	};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient_light);
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	oglEnable(GL_LIGHT0);
#endif
}

int Game_ViewerInitMain(const char *g, const char *d, const char *src, unsigned int lvl)
{
	if(has_init)
		return 0;
	if(!g)
		return 0;
	char *dir = NULL;
	if(d)
		dir = strdup(d);
	else
		dir = strdup(".");
	if(strcasecmp(g, "egypt3d") == 0)
		game = nl_shadow_of_egypt_3d;
	else if(strcasecmp(g, "ct3d") == 0)
		game = nl_contr_terrorism_3d;
	else if(strcasecmp(g, "ct3dep2") == 0)
		game = nl_contr_terrorism_3d_episode_2;
	else if(strcasecmp(g, "specnaz3d") == 0)
		game = nl_army_ranger_3d;
	else if(strcasecmp(g, "clone3d") == 0)
		game = nl_clone_3d;
	else if(strcasecmp(g, "ct3dep3") == 0)
		game = nl_contr_terrorism_3d_episode_3;
	else
	{
		free(dir);
		return 0;
	}
	if(src)
	{
		map_file = strdup(src);
	}
	else
	{
		size_t l = (lvl >= 10 ? 2 : 1);
		size_t len = strlen(dir) + 1 + 3 + l + 4 + 1;
		map_file = NEW_II(char, len);
		sprintf(map_file, "%s/"LEVEL_FILE_SUBFIX, dir, lvl);
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
	return Game_InitGame();
}

void Game_ViewerRegisterFunction(void)
{
	Main3D_SetInitFunction(Game_ViewerInitFunc);
	Main3D_SetDrawFunction(Game_ViewerDrawFunc);
	Main3D_SetIdleEventFunction(Game_ViewerIdleEventFunc);
	Main3D_SetFreeFunction(Game_ViewerFreeFunc);
	Main3D_SetKeyEventFunction(Game_ViewerKeyFunc);
	Main3D_SetReshapeFunction(Game_ViewerReshapeFunc);
	Main3D_SetMouseEventFunction(Game_ViewerMouseEventFunc);
	Main3D_SetMouseMotionEventFunction(Game_ViewerMouseMotionEventFunc);
	Main3D_SetMouseClickEventFunction(Game_ViewerMouseClickEventFunc);
	const void *slot = SignalSlot_GetAction(PLAY_LEVEL_MUSIC);
	if(slot)
	{
		((void__func__int_int)slot)(game, level);
	}
	if(has_init)
	{
		game_mode.state = running_game_type;
		const void *slot = SignalSlot_GetAction(SET_GAME_STATE);
		if(slot)
			((void__func__int)slot)(game_in_game_state);
	}
}

int Game_InitGame(void)
{
	if(has_init)
		return 0;
	//move_unit_3d = 800;
	turn_unit_3d = FREE_VIEW_ANGLE_UNIT;
	new_particle_spirit(&spirit);


	const void *slot = SignalSlot_GetAction(LOADING_PROGRESS_CALLBACK);
	void__func__int_int_constcharptr loading_progress_func = NULL;
	if(slot)
		loading_progress_func = (void__func__int_int_constcharptr)slot;
	if(loading_progress_func)
		loading_progress_func(0, 20, "Init GL State");
	GLfloat bg_color[] = {1.0, 1.0, 1.0, 1.0};
	OpenGL_InitSimpleFog(FOG_NEAR, FOG_FAR, 0.01f, bg_color);
	oglDisable(GL_FOG);
#ifndef _HARMATTAN_OPENGLES2
	Game_ViewerInitSimpleLight();
#endif

	if(loading_progress_func)
		loading_progress_func(0, 30, "Get game resource");
	new_optical_sight_cross_hair(&opticalsight, height / 2, 1.0, 2.0, X11_COLOR(black), 2.0, X11_COLOR(black));

	new_first_person(&fp, fp_right_hand_type, width, 0.0, 0.1, 0.0, 20, -20, 0, 30, 60, 12);
	new_scene_2d(&bg, 0.0f, 0.0f, width, height, 1.0, left_bottom_anchor_type, Color_GetColor(white_color, 0.0), NULL);

	new_normal_cross_hair(&fps_cross_hair, cross_type, X11_COLOR(white), 20.0, 2.0, 20.0);
	new_ray_cross_hair(&tps_ray_cross_hair, ray_type, Color_GetColor(red_color, 0.8), 2.0, 20, 200);
	new_radar(&rad, 100, 90.0, 6000, 1.0, 6.0, X11_COLOR(green), X11_COLOR(red), X11_COLOR(blue), 2.0, X11_COLOR(black), Color_GetColor(black_color, 0.6));

	printf("Read NETLizard map file: %s\n", map_file);
	if(loading_progress_func)
		loading_progress_func(0, 40, "Reading map file");
	switch(game)
	{
		case nl_contr_terrorism_3d:
			map_model = NETLizard_ReadGLCT3DMapModelFile(map_file, level == -1 ? 1 : level);
			break;
		case nl_army_ranger_3d:
			map_model = NETLizard_ReadGLSpecnaz3DMapModelFile(map_file, level == -1 ? 3 : level);
			break;
		case nl_contr_terrorism_3d_episode_2:
			map_model = NETLizard_ReadGLCT3DEp2MapModelFile(map_file, level == -1 ? 3 : level);
			break;
		case nl_shadow_of_egypt_3d:
			map_model = NETLizard_ReadGLEgpyt3DMapModelFile(map_file);
			break;
		case nl_clone_3d:
			map_model = NETLizard_ReadGLClone3DMapModelFile(map_file);
			break;
		case nl_contr_terrorism_3d_episode_3:
			map_model = NETLizard_ReadGLCT3DEp3MapModelFile(map_file, level == -1 ? 1 : level);
			break;
		default:
			break;
	}
	if(map_model)
	{
		if(loading_progress_func)
			loading_progress_func(0, 50, "Read map model successful");
		NETLizard_MakeGL23DModel(map_model);
		bg.tex = map_model -> bg_tex;
		if(loading_progress_func)
			loading_progress_func(0, 60, "Reading map event");
		event = Event_LoadEvent(EVENT_FILE, game, level);
	}
	else
	{
		if(loading_progress_func)
			loading_progress_func(1, 100, "Read map model fail");
		return 0;
	}
	if(loading_progress_func)
		loading_progress_func(0, 70, "Init game setting");
	Game_ViewerGetSetting();
	/*
	x_t_3d = -map_model -> start_pos[0];
	y_t_3d = -map_model -> start_pos[2];
	z_t_3d = map_model -> start_pos[1];
	y_r_3d = Algo_FormatAngle(map_model -> start_angle[1] - 180.0);
	//x_r_3d = map_model -> start_angle[0];
	*/
	nl_vector3_t p = {map_model -> start_pos[0], map_model -> start_pos[1], map_model -> start_pos[2]};
	int scene = Algo_GetPointInAABBInNETLizard3DMap(&p, map_model);

	if(loading_progress_func)
		loading_progress_func(0, 80, "Init game character");
	Game_LoadWeaponModel();
	int cc = CHARACTER_COUNT;
	int gc = GROUP_COUNT;
	Setting_GetSettingInteger(CHARACTER_COUNT_SETTING, &cc);
	Setting_GetSettingInteger(GROUP_COUNT_SETTING, &gc);
	Game_InitCharacter(map_model -> start_pos[0], map_model -> start_pos[1], map_model -> start_pos[2] - (2293760 >> 16), 0.0, map_model -> start_angle[1], scene, gc, cc, my_character_index, NULL);
	player = characters + my_character_index;
	if(god_mode)
	{
		player -> health = -1;
		player -> health_full = -1;
		player -> current_weapon.ammo_total_count = -1;
		player -> current_weapon.ammo_total_count_limit = -1;
	}
	player -> ai.type = ai_player_type;

	int i;
	for(i = 1; i < character_count; i++)
	{
		Game_RandStartPosition(map_model, characters + i, -1);
	}
	frustum_far = FRUSTUM_FAR;
#ifndef _HARMATTAN_OPENGL
	nl_vector3_t min = {0.0, 0.0, 0.0};
	nl_vector3_t max = {0.0, 0.0, 0.0};
	Algo_GetNETLizard3DMapRange(map_model, NULL, 0, &min, &max);
	frustum_far = KARIN_MAX(max.y - min.y, (KARIN_MAX(max.x - min.x, max.z - min.z)));
	//printff(frustum_far);
#endif
	if(loading_progress_func)
		loading_progress_func(0, 90, "Init game mode");
	int point = 200;
	long long gtime = 300;
	Setting_GetSettingInteger(POINT_TARGET_SETTING, &point);
	Setting_GetSettingTime(TIME_LIMIT_SETTING, &gtime);
	new_death_game_mode(&game_mode, third_person_mode, win_point_type, gtime, point, relive_random_place_type, 5, 1);
	Mode_InitDeathGameMode(&game_mode, characters, character_count, map_model, event);
	new_game_menu(&internal_menu);
	new_game_over(&game_over_surface);
	internal_menu.init_func();
	game_over_surface.init_func();
	new_character_status_bar(&status_bar, 0, 0, 0.1, 854.0, 40.0, 0, Color_GetColor(black_color, 0.5), X11_COLOR(green), Color_GetColor(black_color, 0.5), X11_COLOR(green));
	new_reloading_progress_bar(&reloading_bar, 227, 60, 0.2, 400, 40, 0, Color_GetColor(black_color, 0.0), X11_COLOR(green), Color_GetColor(black_color, 0.0), X11_COLOR(white), Color_GetColor(black_color, 0.0));
	new_vkb(&vkb_layer, 0, 0, 0, 854, 480);
	reloading_bar.fnt = &fnt;
	reloading_bar.game_mode = &game_mode;
	status_bar.fnt = &fnt;
	status_bar.game_mode = &game_mode;
	Sound_LoadGameSound();
	new_score_table(&score_tb, 150, 60, 0.05, 554, 360, 400, 20, 1, Color_GetColor(purple_color, 0.4), Color_GetColor(black_color, 0.4), Color_GetColor(orange_color, 0.4), Color_GetColor(green_color, 0.4));
	score_tb.fnt = &fnt;
	score_tb.game_mode = &game_mode;
	if(loading_progress_func)
		loading_progress_func(0, 100, "Start game");
	has_init = 1;
	return 1;
}

void Game_ViewerDrawFunc(void)
{
	if(!has_init)
		return;
	if(game_mode.state == running_game_type)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		int *scenes = NULL;
		unsigned int count = 0;
		person_mode pm = game_mode.p_mode;
		if(zm.type == sniper_zoom_type)
			pm = first_person_mode;

		// 启用瞄准镜，模板测试
		if(zm.type == sniper_zoom_type)
		{
			oglEnable(GL_STENCIL_TEST);
			OpenGL_Render2D(0.0, width, 0.0, height);
			{
				glStencilMask(1);
				glPushMatrix();
				{
					glTranslatef(width / 2, height / 2, 0.0);
					glStencilFunc(GL_NEVER, 1, 1);
					glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
					UI_RenderOpticalSightCrossHair(&opticalsight.optical, sight_optical);
					glStencilFunc(GL_ALWAYS, 0, 1);
					glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
					UI_RenderOpticalSightCrossHair(&opticalsight.optical, sight_front);
				}
				glPopMatrix();
			}
			glStencilFunc(GL_EQUAL, 1, 1);
			glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		}

		// 渲染场景3D / 2D背景
		if(game == nl_shadow_of_egypt_3d && 
				(level == 0 || level == 8 || level == 9 || level == 10 || level == 12))
		{
			OpenGL_Render3D(45, width, height, FRUSTUM_NEAR, frustum_far);
			{
				if(game_mode.characters[game_mode.current_character].scene != -1)
				{
					const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + game_mode.characters[game_mode.current_character].scene;
					unsigned int k;
					for(k = mesh -> item_index_range[0]; k < mesh -> item_index_range[1]; k++)
					{
						const GL_NETLizard_3D_Item_Mesh *im = map_model -> item_meshes + k;
						if(im -> item_type == Item_Box_Type)
						{
							if(!im -> item_mesh.materials)
								break;
							glPushMatrix();
							{
								glRotatef(x_r_3d, 1.0, 0.0 ,0.0);
								glRotatef(y_r_3d, 0.0, 1.0, 0.0);
								glRotatef(-90.0, 1.0, 0.0, 0.0);
								GLfloat xs = im -> item_mesh.ortho[0] - im -> item_mesh.ortho[3];
								GLfloat ys = im -> item_mesh.ortho[1] - im -> item_mesh.ortho[4];
								GLfloat zs = im -> item_mesh.ortho[2] - im -> item_mesh.ortho[5];
								glScalef(frustum_far / xs, frustum_far / ys, frustum_far / zs);
								NETLizard_RenderGL3DMesh(&(im -> item_mesh), map_model -> texes);
							}
							glPopMatrix();
							break;
						}
					}
				}
			}
		}
		else
		{
			if(map_model -> bg_tex)
			{
				OpenGL_Render2D(0.0, width, 0.0, height);
				{
					UI_RenderScene2D(&bg);
				}
			}
		}

#ifndef _HARMATTAN_OPENGLES2
		if(is_lighting)
			oglEnable(GL_LIGHTING);
#endif
		OpenGL_Render3D(zm.foxy, width, height, FRUSTUM_NEAR, frustum_far);
		{
			// 渲染地图场景
			glPushMatrix();
			{
				Main3D_ModelViewTransform(pm, -25.0, -15.0, 120.0, 0);

				if(game_mode.characters[game_mode.current_character].scene != -1)
				{
					if(game == nl_shadow_of_egypt_3d && (level == 8 || level == 9 || level == 12))
					{
						count = 1;
						scenes = NEW_II(GLint, count);
						scenes[0] = game_mode.characters[game_mode.current_character].scene;
					}
					else
					{
						OpenGL_ExtractFrustum(frustum);
						scenes = Algo_GetNETLizard3DMapRenderScenes(map_model, &count, frustum);
					}
				}

				if(scenes)
					NETLizard_RenderGL3DMapModelScene(map_model, scenes, count);
				else
					NETLizard_RenderGL3DModel(map_model);

				Game_RenderCharacters(game_mode.characters, 0, game_mode.current_character, scenes, count);
				Game_RenderCharacters(game_mode.characters, game_mode.current_character + 1, game_mode.character_count, scenes, count);
				// 渲染角色第三人称视角
				if(pm == third_person_mode)
					Game_RenderGameCharacter(game_mode.characters + game_mode.current_character);

				List_ForEachConst(&game_mode.particle_list, Game_RenderGameParticle);

				// 渲染圆点瞄准器
				if(pm == third_person_mode && game_mode.characters[game_mode.current_character].health != health_death_type)
				{
					nl_vector3_t p1 = {0.0, 0.0, 0.0};
					nl_vector3_t p2 = {0.0, 0.0, 0.0};
					float dis1 = 0.0;
					float dis2 = 0.0;
					int r1 = Game_GetRayPointCoord(map_model, game_mode.characters + game_mode.current_character, GL_TRUE, NULL, &p1, NULL, &dis1);
					int r2 = Algo_RayCharacterCollisionTesting(game_mode.characters + game_mode.current_character, game_mode.characters, 0, game_mode.character_count, GL_TRUE, NULL, &dis2, &p2);
					nl_vector3_t collision_point = {0.0, 0.0, 0.0};
					int ray_ava = 1;
					if(r1 && r2)
					{
						if(dis1 < dis2)
							collision_point = p1;
						else
							collision_point = p2;
					}
					else if(r1 && !r2)
						collision_point = p1;
					else if(!r1 && r2)
						collision_point = p2;
					else
						ray_ava = 0;
					if(ray_ava)
					{
						tps_ray_cross_hair.ray.start_pos[0] = game_mode.characters[game_mode.current_character].current_weapon.position[0];
						tps_ray_cross_hair.ray.start_pos[1] = game_mode.characters[game_mode.current_character].current_weapon.position[1];
						tps_ray_cross_hair.ray.start_pos[2] = game_mode.characters[game_mode.current_character].current_weapon.position[2];
						tps_ray_cross_hair.ray.target_pos[0] = collision_point.x;
						tps_ray_cross_hair.ray.target_pos[1] = collision_point.y;
						tps_ray_cross_hair.ray.target_pos[2] = collision_point.z;
#ifndef _HARMATTAN_OPENGLES2
						if(is_lighting)
							oglDisable(GL_LIGHTING);
#endif
						UI_RenderCrossHair(&tps_ray_cross_hair);
#ifndef _HARMATTAN_OPENGLES2
						if(is_lighting)
							oglEnable(GL_LIGHTING);
#endif
					}
				}
			}
			glPopMatrix();
		}

#ifndef _HARMATTAN_OPENGLES2
		if(is_lighting)
			oglDisable(GL_LIGHTING);
#endif
		if(zm.type == sniper_zoom_type)
			oglDisable(GL_STENCIL_TEST);

		OpenGL_Render2D(0.0, width, 0.0, height);
		{
			if(open_radar)
			{
				glPushMatrix();
				{
					glTranslatef(width - rad.radius, height - rad.radius, 0.0);
					UI_RenderRadar(&rad);
				}
				glPopMatrix();
			}
			// 渲染2D主视角
			if(zm.type == no_zoom_type)
			{
				if(pm == first_person_mode && game_mode.characters[game_mode.current_character].health != health_death_type)
				{
					glPushMatrix();
					{
						fps_cross_hair.normal.pos[0] = width / 2;
						fps_cross_hair.normal.pos[1] = height / 2;
						fps_cross_hair.normal.pos[2] = 0.0;
						UI_RenderCrossHair(&fps_cross_hair);
					}
					glPopMatrix();
				}

				if(pm == first_person_mode && game_mode.p_mode == first_person_mode)
				{
					if(game_mode.characters[game_mode.current_character].health != health_death_type)
					{
#ifndef _HARMATTAN_OPENGLES2
						if(is_lighting)
							oglEnable(GL_LIGHTING);
#endif
						if(fp.fp.tex != game_mode.characters[game_mode.current_character].current_weapon.model -> fp_tex)
						{
							UI_SetFirstPersonTexture(&fp, game_mode.characters[game_mode.current_character].current_weapon.model -> fp_tex);
						}
						UI_UpdateFirstPerson(&fp, delta_time);
						UI_RenderFirstPerson(&fp);
#ifndef _HARMATTAN_OPENGLES2
						if(is_lighting)
							oglDisable(GL_LIGHTING);
#endif
					}
				}
			}

			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, 0.4);
				UI_RenderCharacterStatusBar(&status_bar);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(reloading_bar.x, reloading_bar.y, reloading_bar.z);
				UI_RenderReloadingProgressBar(&reloading_bar);
			}
			glPopMatrix();

			if(score_tb.visible)
			{
				glPushMatrix();
				{
					glTranslatef(score_tb.x, score_tb.y, score_tb.z);
					UI_RenderScoreTable(&score_tb);
				}
				glPopMatrix();
			}

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
				const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + game_mode.characters[game_mode.current_character].scene;
				Font_RenderString(&fnt, 4, height - 8 * fnt.height, 0.0, 1.0, 0.0, 1.0, map_file);
				nl_vector3_t dir = Algo_ComputeDirection(game_mode.characters[game_mode.current_character].y_angle, game_mode.characters[game_mode.current_character].x_angle);
				sprintf(str, "Pos -> (%.2f, %.2f, %.2f)", game_mode.characters[game_mode.current_character].position[0], game_mode.characters[game_mode.current_character].position[1], game_mode.characters[game_mode.current_character].position[2]);
				Font_RenderString(&fnt, 4, height - 9 * fnt.height, 0.0, 1.0, 0.0, 1.0, str);
				sprintf(str, "Ang -> (%.0f, %.0f) Dir -> (%.2f, %.2f, %.2f)", game_mode.characters[game_mode.current_character].x_angle, game_mode.characters[game_mode.current_character].y_angle, dir.x, dir.y, dir.z);
				Font_RenderString(&fnt, 4, height - 10 * fnt.height, 0.0, 1.0, 0.0, 1.0, str);
				sprintf(str, "Scene -> (%d / %d) Item -> %d (%d, %d)", game_mode.characters[game_mode.current_character].scene, map_model -> count, game_mode.characters[game_mode.current_character].collision_item, mesh -> item_index_range[0], mesh -> item_index_range[1]);
				Font_RenderString(&fnt, 4, height - 11 * fnt.height, 0.0, 1.0, 0.0, 1.0, str);
				sprintf(str, "y -> %d x -> %d dis -> %d", tp_y_offset, tp_x_offset, tp_dis);
				Font_RenderString(&fnt, 4, height - 12 * fnt.height, 0.0, 1.0, 0.0, 1.0, str);
				if(last_key != Harmattan_Total_Key)
				{
					sprintf(str, "%s - %s", Key_Infos[last_key].symbol, last_pressed ? "pressed" : "released");
					Font_RenderString(&fnt, 4, height - 13 * fnt.height, 0.0, 1.0, 0.0, 1.0, str);
				}
			}
		}
		if(scenes)
			free(scenes);
	}
	else if(game_mode.state == pause_game_type)
	{
		internal_menu.draw_func();
	}
	else if(game_mode.state == finish_game_type)
	{
		game_over_surface.draw_func();
	}
}

void Game_ViewerFreeFunc(void)
{
	if(!has_init)
		return;
	delete_death_game_mode(&game_mode);
	FREE_PTR(map_file)
		if(map_model)
		{
			delete_GL_NETLizard_3D_Model(map_model);
			free(map_model);
			map_model = NULL;
		}
	Event_FreeEvent(event);
	event = NULL;
	bg.tex = NULL;
	fp.fp.tex = NULL;
	delete_scene_2d(&bg);
	delete_first_person(&fp);
	delete_optical_sight(&opticalsight.optical);
	delete_score_table(&score_tb);

	Game_DeleteCharacter(characters, character_count);

	delete_radar(&rad);
	delete_particle_spirit(&spirit);	
	delete_character_status_bar(&status_bar);
	delete_reloading_progress_bar(&reloading_bar);
	delete_vkb(&vkb_layer);
	internal_menu.free_func();
	game_over_surface.free_func();
	Game_ResetViewer();
	Sound_FreeGameSound();
	Game_FreeWeaponModel();
	has_init = 0;
}

void Game_UpdateFPPosition(const game_character *c)
{
	if(!c)
		return;
	if((c -> ai.action & aiaction_attack_type || c -> ai.action & aiaction_fight_type) && c -> current_weapon.status == firing_type)
		UI_UpdateFirstPersonStatus(&fp, fp_fight_status_type);
	else if(c -> ai.action & aiaction_movexyz_type || c -> ai.action & aiaction_jump_type)
		UI_UpdateFirstPersonStatus(&fp, fp_move_status_type);
	else if(c -> ai.action & aiaction_turnleft_type)
		UI_UpdateFirstPersonStatus(&fp, fp_turnleft_status_type);
	else if(c -> ai.action & aiaction_turnright_type)
		UI_UpdateFirstPersonStatus(&fp, fp_turnright_status_type);
	else if(c -> ai.action & aiaction_turndown_type)
		UI_UpdateFirstPersonStatus(&fp, fp_turndown_status_type);
	else if(c -> ai.action & aiaction_turnup_type)
		UI_UpdateFirstPersonStatus(&fp, fp_turnup_status_type);
	else
		UI_UpdateFirstPersonStatus(&fp, fp_idle_status_type);
}

void Game_UpdateZoomProgress(void)
{
	if(!has_init)
		return;
	if(game_mode.state != running_game_type)
		return;
	if(zm.type == no_zoom_type)
		return;
	if(player -> health == health_death_type)
	{
		zm.type = no_zoom_type;
		zm.foxy = zm.max_foxy;
		zm.zoom_out_unit = 0;
		zm.zoom_in_unit = 0;
		zm.zoom_state = 0;
	}
	else
	{
		if(zm.zoom_state > 0)
		{
			zm.foxy -= zm.zoom_out_unit * delta_time;
			if(zm.foxy < zm.min_foxy)
			{
				zm.foxy = zm.min_foxy;
				zm.zoom_state = 0;
			}
		}
		else if(zm.zoom_state < 0)
		{
			zm.foxy += zm.zoom_in_unit * delta_time;
			if(zm.foxy > zm.max_foxy)
			{
				zm.type = no_zoom_type;
				zm.foxy = zm.max_foxy;
				zm.zoom_state = 0;
			}
		}
	}
}

// 指定角色，来更新视觉坐标
void Game_UpdateGLTransform(game_character *gamer)
{
	if(!has_init)
		return;
	if(!gamer)
		return;
	x_t_3d = -gamer -> position[0];
	y_t_3d = -gamer -> position[2] - gamer -> height;
	z_t_3d = gamer -> position[1];
	x_r_3d = gamer -> x_angle;
	y_r_3d = Algo_FormatAngle(-gamer -> y_angle - 180.0);

	if(game_mode.p_mode == third_person_mode)
	{
		gl_vector3_t third = {0.0, 0.0, 0.0};
		//if(Algo_UpdateThirdPersonPosition(&third.x, &third.y, &third.z, x_t_3d, y_t_3d, z_t_3d, x_r_3d, y_r_3d, -27.0, 15.0, 180.0, gamer -> scene, gamer -> scene_collision_result))
		float rxr = 0.0;
		float ryr = 0.0;
		if(gamer -> ai.action == aiaction_dead_type && gamer -> score.killed_character != -1)
		{
			view_free_reason = view_game_free_type;
			view_free_mode = GL_TRUE;
			float xr = 0.0;
			float yr = 0.0;
			Game_ComputeCharacterAndCharacterAngle(gamer, game_mode.characters + gamer -> score.killed_character, &yr, &xr);
			/*
			gamer -> x_angle = xr;
			gamer -> current_weapon.x_angle = gamer -> x_angle;
			*/
			view_y_angle = yr;//Algo_FormatAngle(yr - game_mode.gamer -> y_angle);
			view_x_angle = xr;//Algo_FormatAngle(xr - game_mode.gamer -> x_angle);
		}
		else
		{
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
					if(Algo_FormatAngle(view_y_angle - gamer -> y_angle) > 180.0)
						view_y_angle = Algo_FormatAngle(gamer -> y_angle + 180.0);
						*/
				}
				else if(action_state[FreeViewTurnLeft_Action] == 0 && action_state[FreeViewTurnRight_Action])
				{
					view_y_angle = Algo_FormatAngle(view_y_angle - r);
					/*
					if(Algo_FormatAngle(view_y_angle - gamer -> y_angle) < 180.0)
						view_y_angle = Algo_FormatAngle(gamer -> y_angle - 180.0);
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
				view_y_angle = gamer -> y_angle;
				*/
		}

		if(Algo_ComputeThirdPersonPosition(map_model, gamer, tp_y_offset, tp_x_offset, tp_dis, is_cross, view_free_mode, view_y_angle, view_x_angle, &third, &ryr, &rxr))
		{
			tp_x_t_3d = third.x;
			tp_y_t_3d = third.y;
			tp_z_t_3d = third.z;
			tp_y_r_3d = ryr;
			tp_x_r_3d = rxr;
			/*
				 gamer -> current_weapon.position[0] = -third.x;
				 gamer -> current_weapon.position[1] = third.z;
				 gamer -> current_weapon.position[2] = -third.y;
				 gamer -> current_weapon.x_angle = Algo_FormatAngle(gamer -> x_angle + 15);
				 gamer -> current_weapon.y_angle = Algo_FormatAngle(gamer -> y_angle + 27);
				 */
		}
	}
	if(gamer -> ai.action == aiaction_dead_type && gamer -> score.killed_character != -1)
	{
		float xr = 0.0;
		float yr = 0.0;
		Game_ComputeCharacterAndCharacterAngle(gamer, game_mode.characters + gamer -> score.killed_character, &yr, &xr);
		x_r_3d = xr;
		y_r_3d = Algo_FormatAngle(-yr - 180.0);
		y_t_3d = -gamer -> position[2] - gamer -> width / 2;
		tp_y_t_3d = y_t_3d;
	}
}

// 接收按键操作动作来更新动作
int Game_UpdatePlayerAI(Game_Action a, int p)
{
	if(!has_init)
		return 0;
	if(game_mode.state != running_game_type)
		return 0;
	if(!player)
		return 0;
	if(a == Total_Action)
		return 0;
	if(player -> ai.action & aiaction_dead_type)
		return 0;
	int r = 1;
	switch(a)
	{
		case Forward_Action:
			if((!p && (player -> ai.action & aiaction_moveforward_type)) || (p && (player -> ai.action & aiaction_moveforward_type) == 0))
				player -> ai.action ^= aiaction_moveforward_type;
			break;
		case Backward_Action:
			if((!p && (player -> ai.action & aiaction_movebackward_type)) || (p && (player -> ai.action & aiaction_movebackward_type) == 0))
				player -> ai.action ^= aiaction_movebackward_type;
			break;
		case MoveLeft_Action:
			if((!p && (player -> ai.action & aiaction_moveleft_type)) || (p && (player -> ai.action & aiaction_moveleft_type) == 0))
				player -> ai.action ^= aiaction_moveleft_type;
			break;
		case MoveRight_Action:
			if((!p && (player -> ai.action & aiaction_moveright_type)) || (p && (player -> ai.action & aiaction_moveright_type) == 0))
				player -> ai.action ^= aiaction_moveright_type;
			break;
		case MoveUp_Action:
			if((!p && (player -> ai.action & aiaction_moveup_type)) || (p && (player -> ai.action & aiaction_moveup_type) == 0))
				player -> ai.action ^= aiaction_moveup_type;
			break;
		case MoveDown_Action:
			if((!p && (player -> ai.action & aiaction_movedown_type)) || (p && (player -> ai.action & aiaction_movedown_type) == 0))
				player -> ai.action ^= aiaction_movedown_type;
			break;
		case TurnLeft_Action:
			if((!p && (player -> ai.action & aiaction_turnleft_type)) || (p && (player -> ai.action & aiaction_turnleft_type) == 0))
				player -> ai.action ^= aiaction_turnleft_type;
			break;
		case TurnRight_Action:
			if((!p && (player -> ai.action & aiaction_turnright_type)) || (p && (player -> ai.action & aiaction_turnright_type) == 0))
				player -> ai.action ^= aiaction_turnright_type;
			break;
		case TurnUp_Action:
			if((!p && (player -> ai.action & aiaction_turnup_type)) || (p && (player -> ai.action & aiaction_turnup_type) == 0))
				player -> ai.action ^= aiaction_turnup_type;
			break;
		case TurnDown_Action:
			if((!p && (player -> ai.action & aiaction_turndown_type)) || (p && (player -> ai.action & aiaction_turndown_type) == 0))
				player -> ai.action ^= aiaction_turndown_type;
			break;
		case Attack_Action:
			if(p && player -> current_weapon.ammo_total_count != 0)
			{
				if(player -> current_weapon.type <= short_attack_type)
				{
					player -> ai.action |= aiaction_fight_type;
					player -> ai.fighting = 1;
				}
				else
				{
					player -> ai.action |= aiaction_attack_type;
				}
			}
			else
			{
				if(player -> ai.action & aiaction_attack_type)
					player -> ai.action ^= aiaction_attack_type;
				else if(player -> ai.action & aiaction_fight_type)
					player -> ai.action ^= aiaction_fight_type;
			}
			break;
		case Jump_Action:
			if(p)
			{
				if(player -> z_moving.state == no_z_type)
				{
					player -> z_moving.state = z_jumping_type;
					player -> z_moving.start_z = player -> position[2];
					player -> z_moving.start_time = game_mode.game_time;
					player -> z_moving.jump_speed = -player -> z_jump_speed;
					player -> z_moving.speed = player -> z_moving.jump_speed;
				}
			}
			break;
		case Reload_Action:
			if(p)
			{
				if(Game_ReloadWeapon(&player -> current_weapon, player -> ai.time))
					player -> ai.action |= aiaction_reload_type;
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
				game_character *c = game_mode.characters + game_mode.current_character;
				view_x_angle = c -> x_angle;
				view_y_angle = c -> y_angle;
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
				game_character *c = game_mode.characters + game_mode.current_character;
				view_x_angle = c -> x_angle;
				view_y_angle = c -> y_angle;
			}
			break;
		default:
			r = 0;
			break;
	}
	return r;
}

int Game_ViewerIdleEventFunc(void)
{
	if(!has_init)
		return 0;
	if(game_mode.state == running_game_type)
	{
		//player -> health = health_full_type;
		Mode_DeathGameModeMain(&game_mode, fps, delta_time);
		if(game_mode.state == finish_game_type)
		{
			Game_GameOver();
			return 1;
		}
		Game_UpdateZoomProgress();

		game_character *c = game_mode.characters + game_mode.current_character;
		Game_UpdateGLTransform(c);

		fps_cross_hair.normal.scale = game_mode.characters[game_mode.current_character].current_weapon.firing_progress;

		Game_UpdateRadar(game_mode.characters + game_mode.current_character, game_mode.characters, 0, game_mode.character_count, &rad);
		if(game_mode.p_mode == first_person_mode)
			Game_UpdateFPPosition(c);

		if(play_sound)
			List_ForEachConst(&game_mode.sound_list, Game_PlayGameSound);

		return 1;
	}
	else if(game_mode.state == pause_game_type)
	{
		return internal_menu.idle_func();
	}
	else if(game_mode.state == finish_game_type)
	{
		game_over_surface.idle_func();
	}
	return 0;
}

int Game_ViewerKeyFunc(int key, int a, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	if(dbg)
	{
		last_key = key;
		last_pressed = pressed;
	}
	int res = 0;
	if(game_mode.state == running_game_type)
	{
		res = Game_ViewerActionEvent(key, a, pressed);
	}
	else if(game_mode.state == pause_game_type)
	{
		res = internal_menu.key_func(key, a, pressed, x, y);
	}
	else if(game_mode.state == finish_game_type)
	{
		game_over_surface.key_func(key, a, pressed, x, y);
	}

	return res;
}

void Game_ViewerReshapeFunc(int w, int h)
{
	if(!has_init)
		return;
	if(game_mode.state == running_game_type)
	{
#ifdef _HARMATTAN_OPENGL
		glViewport( (w - viewport_width) / 2, (h - viewport_height) / 2, viewport_width, viewport_height);
#else
		glViewport(0, 0, w, h);
#endif
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		UI_ResizeScene2D(&bg, w, h);
	}
	else if(game_mode.state == pause_game_type)
	{
		internal_menu.reshape_func(w, h);
	}
	else if(game_mode.state == finish_game_type)
	{
		game_over_surface.reshape_func(w, h);
	}
}

void Game_UpdateRadar(const game_character *gamer, const game_character characters[], int start, int character_count, radar *r)
{
	if(!has_init)
		return;
	if(!gamer || !characters || !r)
		return;
	int i;
	int count = 0;
	GLfloat *points = NEW_II(GLfloat, 4 * character_count);
	nl_vector3_t me = {gamer -> position[0], gamer -> position[1], gamer -> position[2]};
	for(i = start; i < character_count; i++)
	{
		if(gamer == characters + i)
			continue;
		if(characters[i].health == health_death_type)
			continue;
		int g = 0;
		if(gamer -> group == characters[i].group)
			g = 1;
		else if(gamer -> group != characters[i].group)
			g = 2;

		nl_vector3_t p = {characters[i].position[0], characters[i].position[1], characters[i].position[2]};
		nl_vector3_t d = Vector3_SubtractVector3(&p, &me);
		points[count * 4] = d.x;
		points[count * 4 + 1] = d.y;
		points[count * 4 + 2] = d.z;
		points[count * 4 + 3] = g;
		count++;
	}
	free(r -> point_pos);
	r -> rotation = gamer -> y_angle;
	r -> point_pos = points;
	r -> point_count = count;
}

void Game_ViewerInitFunc(void)
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

void Game_AfterGameMenuClosing(void)
{
	if(!has_init)
		return;
	Mode_ContinueGameMode(&game_mode);
	const void *slot = SignalSlot_GetAction(SET_GAME_STATE);
	if(slot)
		((void__func__int)slot)(game_in_game_state);
}

void Game_PauseGameAndOpenMenu(void)
{
	if(!has_init)
		return;
	Mode_PauseGameMode(&game_mode);
	GameMenu_OpenGameMenu();
	const void *slot = SignalSlot_GetAction(SET_GAME_STATE);
	if(slot)
		((void__func__int)slot)(game_in_game_menu_state);
}

int Game_ViewerMouseEventFunc(int b, int p, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(game_mode.state == running_game_type)
	{
		if(open_vkb)
			return UI_VKBMouseEvent(&vkb_layer, b, p ,x, gl_y, Game_ViewerActionEvent);
		else
			return 0;
	}
	else if(game_mode.state == pause_game_type)
	{
		return internal_menu.mouse_func(b, p, x, gl_y);
	}
	else if(game_mode.state == finish_game_type)
	{
		return game_over_surface.mouse_func(b, p, x, gl_y);
	}
	return 0;
}

int Game_ViewerMouseClickEventFunc(int b, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(game_mode.state == pause_game_type)
	{
		return internal_menu.click_func(b, x, gl_y);
	}
	else if(game_mode.state == finish_game_type)
	{
		return game_over_surface.click_func(b, x, gl_y);
	}
	return 0;
}

int Game_ViewerMouseMotionEventFunc(int b, int p, int x, int y, int dx, int dy)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(game_mode.state == running_game_type)
	{
		if(open_vkb)
			return UI_VKBMouseMotionEvent(&vkb_layer, b, p ,x, gl_y, dx, -dy, Game_ViewerActionEvent);
		else
			return 0;
	}
	else if(game_mode.state == pause_game_type)
	{
		return internal_menu.motion_func(b, p, x, gl_y, dx, -dy);
	}
	else if(game_mode.state == finish_game_type)
	{
		return game_over_surface.motion_func(b, p, x, gl_y, dx, -dy);
	}
	return 0;
}

void Game_ResetViewer(void)
{
	last_key = Harmattan_Total_Key;
	last_pressed = 0;
	turn_unit_3d = FREE_VIEW_ANGLE_UNIT;
	player = NULL;
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

	tp_x_offset = 10;
	tp_y_offset = 25;
	tp_dis = 300;

	frustum_far = FRUSTUM_FAR;
	frustum_width = FRUSTUM_WIDTH;
	frustum_height = FRUSTUM_HEIGHT;

	zm.zoom_auto = 0;
	god_mode = 0;
	open_vkb = 1;
	play_sound = 1;
	show_fps = 1;
	open_radar = 1;
	tp_x_offset = 10;
	tp_y_offset = 25;
	tp_dis = 300;

	zm.type = no_zoom_type;
	zm.zoom_state = 0;
	zm.min_foxy = FOXY_MAX;
	zm.max_foxy = FOXY_MAX;
	zm.zoom_out_unit = 0;
	zm.zoom_in_unit = 0;
	zm.foxy = FOXY_MAX;
}

void Game_RenderGameParticle(unsigned int index, const void *data)
{
	if(!has_init)
		return;
	if(!data)
		return;
	const particle *p = (particle *)data;
	if(p -> type == gunfire_particle_type 
			&& ((game_mode.characters[game_mode.current_character].current_weapon.type == sniper_rifle_type && zm.type == sniper_zoom_type)
				|| game_mode.p_mode == first_person_mode))
		return;
	glPushMatrix();
	{
		glTranslatef(p -> pos[0], p -> pos[1], p -> pos[2]);
		glRotatef(p -> y_angle, 0.0f, 0.0f, 1.0f);
		glRotatef(p -> x_angle, 1.0f, 0.0f, 0.0f);
		Particle_RanderParitcle(&spirit, p -> type);
	}
	glPopMatrix();
}

void Game_PlayGameSound(unsigned int index, const void *data)
{
	if(!has_init)
		return;
	if(!data)
		return;
	const sound_effect *s = (sound_effect *)data;
	Sound_PlayGameSound(s);
}

int Game_ViewerActionEvent(int key, int a, int pressed)
{
	if(!has_init)
		return 0;
	int res = 0;
	if(a != Total_Action)
	{
		action_state[a] = pressed ? 1 : 0;
		res = Game_UpdatePlayerAI(a, pressed);
		switch(a)
		{
			case ViewCenter_Action:
				if(pressed)
				{
					if(player -> health != health_death_type)
					{
						player -> x_angle = 0.0;
						player -> current_weapon.x_angle = 0.0;
					}
				}
				break;
			case Quit_Action:
				if(pressed)
				{
					Game_PauseGameAndOpenMenu();
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
				score_tb.visible = pressed ? GL_TRUE : GL_FALSE;
				break;
			case PrevWeapon_Action:
				if(pressed)
				{
					int w = player -> current_weapon.weapon_index;
					do
					{
						w--;
						if(w < ct3d_Dagger)
							w = clone3d_Rocket_Launcher;
						break;
						/*
							 if(w != ct3d_Fragmentation_Grenade && w != ct3d_Flash_Grenade && w != specnaz3d_Fragmentation_Grenade)
							 break;
							 if(w != ct3d_Dagger && w != ct3d_Fragmentation_Grenade && w != ct3d_Flash_Grenade && w != specnaz3d_Dagger && w != specnaz3d_Fragmentation_Grenade && w != egypt3d_The_Sword_of_Osiris && w != egypt3d_Dagger)
							 break;
							 */
					}while(1);
					new_weapon(&player -> current_weapon, w);
					if(god_mode)
					{
						player -> current_weapon.ammo_total_count = -1;
						player -> current_weapon.ammo_total_count_limit = -1;
					}
					if(zm.type != no_zoom_type)
					{
						zm.type = no_zoom_type;
						zm.zoom_state = 0;
						zm.zoom_out_unit = 0;
						zm.zoom_in_unit = 0;
						zm.foxy = zm.max_foxy;
					}
					res = 1;
				}
				break;
			case NextWeapon_Action:
				if(pressed)
				{
					int w = player -> current_weapon.weapon_index;
					do
					{
						w++;
						if(w > clone3d_Rocket_Launcher)
							w = ct3d_Dagger;
						break;
						/*
							 if(w != ct3d_Fragmentation_Grenade && w != ct3d_Flash_Grenade && w != specnaz3d_Fragmentation_Grenade)
							 break;
							 if(w != ct3d_Dagger && w != ct3d_Fragmentation_Grenade && w != ct3d_Flash_Grenade && w != specnaz3d_Dagger && w != specnaz3d_Fragmentation_Grenade && w != egypt3d_The_Sword_of_Osiris && w != egypt3d_Dagger)
							 break;
							 */
					}while(1);
					new_weapon(&player -> current_weapon, w);
					if(god_mode)
					{
						player -> current_weapon.ammo_total_count = -1;
						player -> current_weapon.ammo_total_count_limit = -1;
					}
					if(zm.type != no_zoom_type)
					{
						zm.type = no_zoom_type;
						zm.zoom_state = 0;
						zm.foxy = zm.max_foxy;
						zm.zoom_out_unit = 0;
						zm.zoom_in_unit = 0;
					}
					res = 1;
				}
				break;
			case ZoomOut_Action:
				if(game_mode.current_character == my_character_index)
				{
					if(zm.type == no_zoom_type)
					{
						int zv = 0;
						if(player -> current_weapon.type == sniper_rifle_type)
						{
							zm.type = sniper_zoom_type;
							zm.min_foxy = FOXY_MIN;
							zm.max_foxy = FOXY_MAX;
							zm.zoom_out_unit = FOXY_ZOOM_OUT_UNIT;
							zm.zoom_in_unit = FOXY_ZOOM_IN_UNIT;
							zv = 1;
						}
						else if(game_mode.p_mode == third_person_mode)
						{
							zm.type = third_person_zoom_type;
							zm.min_foxy = TP_FOXY_MIN;
							zm.max_foxy = FOXY_MAX;
							zm.zoom_out_unit = FP_FOXY_ZOOM_OUT_UNIT;
							zm.zoom_in_unit = FP_FOXY_ZOOM_IN_UNIT;
							zv = 1;
						}
						else
							zm.type = no_zoom_type;
						if(zv)
						{
							if(pressed)
							{
								zm.zoom_state = 1;
								res = 1;
							}
						}
					}
					else
					{
						if(zm.zoom_auto && !pressed)
						{
							zm.zoom_state = -1;
							res = 1;
						}
					}
				}
				break;
			case ZoomIn_Action:
				if(game_mode.current_character == my_character_index)
				{
					if(zm.type != no_zoom_type)
					{
						if(pressed)
						{
							zm.zoom_state = -1;
							res = 1;
						}
					}
				}
				break;
			case PersonMode_Action:
				if(pressed)
				{
					game_mode.p_mode ^= third_person_mode;
					if(zm.type == third_person_zoom_type)
					{
						zm.zoom_state = 0;
						zm.foxy = zm.max_foxy;
						zm.type = no_zoom_type;
						zm.zoom_out_unit = 0;
						zm.zoom_in_unit = 0;
					}
					res = 1;
				}
				break;
			case OperateGo_Action:
				if(pressed)
				{
					Game_OperateAIMoveToPosition(game_mode.map, player, game_mode.characters, 0, game_mode.character_count);
					res = 1;
				}
				break;
			case OperateBack_Action:
				if(pressed)
				{
					Game_OperateAIBackToMe(game_mode.map, player, game_mode.characters, 0, game_mode.character_count);
					res = 1;
				}
				break;
			case OperateStand_Action:
				if(pressed)
				{
					Game_OperateAIStandBy(game_mode.map, player, game_mode.characters, 0, game_mode.character_count);
					res = 1;
				}
				break;
			case OpenRadar_Action:
				if(pressed)
				{
					open_radar ^= 1;
					Setting_SetSettingBoolean(OPEN_RADAR_SETTING, open_radar);
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
				if(pressed)
				{
					if(oglIsEnabled(GL_FOG))
						oglDisable(GL_FOG);
					else
						oglEnable(GL_FOG);
					res = 1;
				}
				break;
			case Harmattan_K_Control_R:
			case Harmattan_K_Control_L:
				if(pressed)
				{
					is_cross ^= 1;
					float x = Algo_FormatAngle(x_r_3d);
					if(!is_cross && (x > 90 && x < 270))
						x_r_3d = 0;
					res = True;
				}
				break;
			case Harmattan_K_less:
				if(pressed)
				{
					Event_FreeEvent(event);
					event = NULL;
					event = Event_LoadEvent(EVENT_FILE, game, level);
					res = 1;
				}
				break;
			case Harmattan_K_at:
				if(pressed)
				{
					if(game_mode.current_character > 0)
						game_mode.current_character--;
					else
						game_mode.current_character = character_count - 1;
					if(zm.type != no_zoom_type)
					{
						zm.type = no_zoom_type;
						zm.foxy = zm.max_foxy;
						zm.zoom_state = 0;
						zm.zoom_out_unit = 0;
						zm.zoom_in_unit = 0;
					}
					res = 1;
				}
				break;
			case Harmattan_K_question:
				if(pressed)
				{
					if(game_mode.current_character < character_count - 1)
						game_mode.current_character++;
					else
						game_mode.current_character = 0;
					if(zm.type != no_zoom_type)
					{
						zm.type = no_zoom_type;
						zm.foxy = zm.max_foxy;
						zm.zoom_state = 0;
						zm.zoom_out_unit = 0;
						zm.zoom_in_unit = 0;
					}
					res = 1;
				}
				break;
			case Harmattan_K_parenright:
				if(pressed)
				{
					int i;
					for(i = 0; i < game_mode.character_count; i++)
					{
						if(1 || game_mode.characters[i].health == health_death_type)
						{
							game_mode.characters[i].health = game_mode.characters[i].health_full;
							Game_RandStartPosition(game_mode.map, game_mode.characters + i, -1);
						}
					}
					res = 1;
				}
				break;
			case Harmattan_K_underscore:
				if(pressed)
				{
					/*
						 player -> health = player -> health == health_death_type ? health_full_type : health_death_type;
						 player -> score.death++;
						 */
					Game_OperateAIGoMe(game_mode.map, player,  game_mode.characters, 0, game_mode.character_count);
					res = 1;
				}
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
					if(god_mode)
					{
						player -> health = -1;
						player -> health_full = -1;
						player -> current_weapon.ammo_total_count = -1;
						player -> current_weapon.ammo_total_count_limit = -1;
					}
					else
					{
						player -> health = health_full_type;
						player -> health_full = health_full_type;
						new_weapon(&player -> current_weapon, player -> current_weapon.weapon_index);
					}
					res = 1;
				}
				break;
			default:
				break;
		}
	}
	return res;
}

void Game_ViewerGetSetting(void)
{
	char b = 0;
	if(Setting_GetSettingBoolean(ZOOM_AUTO_SETTING, &b))
		zm.zoom_auto = b;
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
}

void Game_ReplayGame(void)
{
	if(!has_init)
		return;
	if(game_mode.state != finish_game_type)
		return;
	//game_over_surface.free_func();
	Mode_ResetGameMode(&game_mode);
	int i;
	for(i = 0; i < game_mode.character_count; i++)
	{
		Game_RandStartPosition(map_model, game_mode.characters + i, -1);
		if(game_mode.characters[i].current_weapon.type > short_attack_type)
			Game_ChangeRandLongWeapon(&game_mode.characters[i].current_weapon);
	}
	nl_vector3_t p = {map_model -> start_pos[0], map_model -> start_pos[1], map_model -> start_pos[2]};
	int scene = Algo_GetPointInAABBInNETLizard3DMap(&p, map_model);
	player -> position[0] = map_model -> start_pos[0];
	player -> position[1] = map_model -> start_pos[1];
	player -> position[2] = map_model -> start_pos[2] - (2293760 >> 16);
	player -> x_angle = 0.0;
	player -> y_angle = map_model -> start_angle[1];
	player -> scene = scene;
	delete_weapon(&player -> current_weapon);
	int wpi = clone3d_M16;
	Setting_GetSettingInteger(USE_WEAPON_SETTING, &wpi);
	new_weapon(&player -> current_weapon, wpi);
	if(god_mode)
	{
		player -> health = -1;
		player -> health_full = -1;
		player -> current_weapon.ammo_total_count = -1;
		player -> current_weapon.ammo_total_count_limit = -1;
	}

	view_y_angle = 0.0;
	view_x_angle = 0.0;
	view_free_reason = view_auto_free_type;
	view_free_mode = GL_FALSE;

	zm.type = no_zoom_type;
	zm.zoom_state = 0;
	zm.min_foxy = FOXY_MAX;
	zm.max_foxy = FOXY_MAX;
	zm.zoom_out_unit = 0;
	zm.zoom_in_unit = 0;
	zm.foxy = FOXY_MAX;
}

void Game_GameOver(void)
{
	if(!has_init)
		return;
	if(game_mode.state != finish_game_type)
		return;
	const void *slot = SignalSlot_GetAction(SET_GAME_STATE);
	if(slot)
	{
		((void__func__int)slot)(game_in_over_state);
	}
	GameMenu_OpenGameOver(&game_mode);
}
