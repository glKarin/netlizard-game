#include "netlizard_viewer.h"
#include "gl_3d_main.h"
#include "nl_algo.h"
#include "gl_util.h"
#include "nl_gl.h"
#include "game_util.h"
#include "nl_event.h"
#include "math3d/algo.h"
#include "game/character.h"
#include "netlizard/nl_util.h"
#include "nl_game.h"
#include "cross_hair.h"
#include "physics/gravity.h"

// lvl

#define COLLISION_WIDTH 50 // 40 // 40 * 2
#define COLLISION_HEIGHT 180 // 190
#define FULL_COLLISION_HEIGHT 250 // 236
#define FALLDOWN_UNIT 60.0
#define JUMP_UNIT 60.0
#define MAX_JUMPING_HEIGHT 180.0
#define FOXY_MAX 45.0

#define FOG_NEAR 3000.0
#define FOG_FAR 5000.0

#define FRUSTUM_NEAR 0.1
#define FRUSTUM_FAR 4000.0
#define FRUSTUM_WIDTH 360
#define FRUSTUM_HEIGHT 200

#define FP_FILE _KARIN_RESOURCE_DIR"resource/c%d.png"
#define EVENT_FILE _KARIN_RESOURCE_DIR"resource/lvl.event"

static person_mode p_mode = third_person_mode;
static game_character player;
static long long time = 0;
static GLfloat frustum[6][4];
static game_name game;
static char *map_file = NULL;
static bool_t dbg = 1;
static bool_t is_lighting = 0;
static scene_2d bg;
static cross_hair fps_cross_hair;
static cross_hair tps_ray_cross_hair;
static GL_NETLizard_3D_Model *map_model = NULL;
static int level = -1;
static double foxy = FOXY_MAX;
static unsigned int view_free_reason = view_auto_free_type;

static NETLizard_Event *ev = NULL;
static int ev_count = 0;
static int tp_x_offset = 10;
static int tp_y_offset = 25;
static int tp_dis = 300;

static GLdouble frustum_far = FRUSTUM_FAR;
static GLuint frustum_width = FRUSTUM_WIDTH;
static GLuint frustum_height = FRUSTUM_HEIGHT;

static void Viewer_NETLizard3DMapInitFunc(void);
static void Viewer_NETLizard3DMapDrawFunc(void);
static void Viewer_NETLizard3DMapFreeFunc(void);
static int Viewer_NETLizard3DMapIdleEventFunc(void);
static void Viewer_NETLizard3DMapReshapeFunc(int w, int h);
static int Viewer_NETLizard3DMapKeyFunc(int key, int a, int pressed, int x, int y);
static void Viewer_NETLizard3DMapInitSimpleLight(void);
static void Viewer_HandleNETLizard3DMapEvent(float delta);
static void Viewer_LoadNETLizard3DMapEvent(void);

static void Viewer_UpdateGLTransform(game_character *gamer);
static void Viewer_UpdatePlayerPosition(void);
static int Viewer_UpdatePlayerAI(Game_Action a, int p);

void Viewer_NETLizard3DMapInitSimpleLight(void)
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

int Viewer_NETLizard3DMapInitMain(const char *g, const char *d, const char *src, unsigned int lvl)
{
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
	nlSetResourcePath(game, dir);
	free(dir);
	return 1;
}

void Viewer_NETLizard3DMapRegisterFunction(void)
{
	Main3D_SetInitFunction(Viewer_NETLizard3DMapInitFunc);
	Main3D_SetDrawFunction(Viewer_NETLizard3DMapDrawFunc);
	Main3D_SetIdleEventFunction(Viewer_NETLizard3DMapIdleEventFunc);
	Main3D_SetFreeFunction(Viewer_NETLizard3DMapFreeFunc);
	Main3D_SetKeyEventFunction(Viewer_NETLizard3DMapKeyFunc);
	Main3D_SetReshapeFunction(Viewer_NETLizard3DMapReshapeFunc);
	Main3D_SetMouseEventFunction(NULL);
	Main3D_SetMouseMotionEventFunction(NULL);
	Main3D_SetMouseClickEventFunction(NULL);
}

void Viewer_NETLizard3DMapInitFunc(void)
{
	Viewer_Init3DFunc();
	GLfloat bg_color[] = {1.0, 1.0, 1.0, 1.0};
	OpenGL_InitSimpleFog(FOG_NEAR, FOG_FAR, 0.1f, bg_color);
	oglDisable(GL_FOG);
#ifndef _HARMATTAN_OPENGLES2
	Viewer_NETLizard3DMapInitSimpleLight();
#endif

	glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);

	move_unit_3d = 50;
	turn_unit_3d = 120;

	viewport_width = frustum_width;
	viewport_height = frustum_height;

	x_a_3d = -90;
	view_y_angle = 0.0;
	view_x_angle = 0.0;
	view_free_reason = view_auto_free_type;
	view_free_mode = GL_FALSE;

	new_scene_2d(&bg, 0.0f, 0.0f, 854.0f, 480.0f, 1.0, left_bottom_anchor_type, Color_GetColor(white_color, 0.0), NULL);

	new_normal_cross_hair(&fps_cross_hair, cross_type, X11_COLOR(white), 20.0, 2.0, 20.0);
	new_ray_cross_hair(&tps_ray_cross_hair, ray_type, Color_GetColor(red_color, 0.8), 1.0, 2.0, 16.0);

	printfs(map_file);
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
		time = Game_GetGameTime();
		NETLizard_MakeGL23DModel(map_model);
		bg.tex = map_model -> bg_tex;
		Viewer_LoadNETLizard3DMapEvent();
	}
	else
		return;
	x_t_3d = -map_model -> start_pos[0];
	y_t_3d = -map_model -> start_pos[2];
	z_t_3d = map_model -> start_pos[1];
	y_r_3d = Algo_FormatAngle(map_model -> start_angle[1] - 180.0);
	//x_r_3d = map_model -> start_angle[0];
	
	nl_vector3_t p = {map_model -> start_pos[0], map_model -> start_pos[1], map_model -> start_pos[2]};
	int scene = Algo_GetPointInAABBInNETLizard3DMap(&p, map_model);

	new_game_character(&player, caitlyn_original, map_model -> start_pos[0], map_model -> start_pos[1], map_model -> start_pos[2] - (2293760 >> 16), 0.0, map_model -> start_angle[1], 0, "karin", scene, clone3d_M16);
	player.ai.type = ai_player_type;
	player.ai.time = time;

	frustum_far = FRUSTUM_FAR;
#ifndef _HARMATTAN_OPENGL
	nl_vector3_t min = {0.0, 0.0, 0.0};
	nl_vector3_t max = {0.0, 0.0, 0.0};
	Algo_GetNETLizard3DMapRange(map_model, NULL, 0, &min, &max);
	frustum_far = KARIN_MAX(max.y - min.y, (KARIN_MAX(max.x - min.x, max.z - min.z)));
	printff(frustum_far);
#endif
}

void Viewer_NETLizard3DMapDrawFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int *scenes = NULL;
	unsigned int count = 0;

	// 渲染场景3D / 2D背景
	if(game == nl_shadow_of_egypt_3d && 
			(level == 0 || level == 8 || level == 9 || level == 10 || level == 12))
	{
		OpenGL_Render3D(45, width, height, FRUSTUM_NEAR, frustum_far);
		{
			if(player.scene != -1)
			{
				const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + player.scene;
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
	OpenGL_Render3D(foxy, width, height, FRUSTUM_NEAR, frustum_far);
	{
		// 渲染地图场景
		glPushMatrix();
		{
			Main3D_ModelViewTransform(p_mode, -25.0, -15.0, 120.0, 0);

			if(player.scene != -1 && game == nl_shadow_of_egypt_3d && (level == 8 || level == 9 || level == 12))
			{
				count = 1;
				scenes = NEW_II(GLint, count);
				scenes[0] = player.scene;
			}
			else
			{
				OpenGL_ExtractFrustum(frustum);
				scenes = Algo_GetNETLizard3DMapRenderScenes(map_model, &count, frustum);
			}
			if(scenes)
			{
				NETLizard_RenderGL3DMapModelScene(map_model, scenes, count);
			}
			else
			{
				NETLizard_RenderGL3DModel(map_model);
			}

			// 渲染角色第三人称视角
			if(p_mode == third_person_mode)
			{
				Game_RenderGameCharacter(&player);
			}

			// 渲染圆点瞄准器
			nl_vector3_t collision_point = {0.0, 0.0, 0.0};
			int scene = -1;
			int r = Game_GetRayPointCoord(map_model, &player, GL_FALSE, &scene, &collision_point, NULL, NULL);
			if(r)
			{
				tps_ray_cross_hair.ray.start_pos[0] = player.current_weapon.position[0];
				tps_ray_cross_hair.ray.start_pos[1] = player.current_weapon.position[1];
				tps_ray_cross_hair.ray.start_pos[2] = player.current_weapon.position[2];
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
		glPopMatrix();
	}

#ifndef _HARMATTAN_OPENGLES2
	if(is_lighting)
		oglDisable(GL_LIGHTING);
#endif

	OpenGL_Render2D(0.0, width, 0.0, height);
	{
		// 渲染2D主视角
		if(p_mode == first_person_mode)
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
	}

	// 渲染调试文本
	if(dbg)
	{
		char str[100];
		memset(str, '\0', 100 * sizeof(char));
		const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + player.scene;
		Font_RenderString(&fnt, 4, height - 2 * fnt.height, 0.0, 0.0, 0.0, 1.0, map_file);
		sprintf(str, "Pos -> [%.2f, %.2f, %.2f] Ang -> [%.0f, %.0f]", -x_t_3d, z_t_3d, -y_t_3d, Algo_FormatAngle(-y_r_3d - 180.0), x_r_3d);
		Font_RenderString(&fnt, 4, height - 4 * fnt.height, 0.0, 0.0, 0.0, 1.0, str);
		sprintf(str, "Scene -> (%d / %d) Item -> %d (%d, %d)", player.scene, map_model -> count, player.collision_item, mesh -> item_index_range[0], mesh -> item_index_range[1]);
		Font_RenderString(&fnt, 4, height - 6 * fnt.height, 0.0, 0.0, 0.0, 1.0, str);
		sprintf(str, "FPS -> %d", fps);
		Font_RenderString(&fnt, 4, height - 8 * fnt.height, 1.0, 0.0, 0.0, 1.0, str);
		sprintf(str, "y -> %d x -> %d dis -> %d", tp_y_offset, tp_x_offset, tp_dis);
		Font_RenderString(&fnt, 4, height - 10 * fnt.height, 0.0, 0.0, 0.0, 1.0, str);
#if 0
		Font_RenderString(&fnt, 4, 6 * fnt.height, 0.0, 0.0, 0.0, 1.0, str);
		if(scenes)
		{
			unsigned int i;
			for(i = 0; i < count; i++)
			{
				if(scenes[i] == player.scene)
					Font_RenderDigit(&fnt, 4 + i * FONT_WIDTH * 8, 8 * fnt.height, 0.0, 0.0, 1.0, 1.0, scenes[i]);
				else
					Font_RenderDigit(&fnt, 4 + i * FONT_WIDTH * 8, 8 * fnt.height, 0.0, 0.0, 0.0, 1.0, scenes[i]);
			}
		}
#endif
	}
	if(scenes)
		free(scenes);
}

void Viewer_NETLizard3DMapFreeFunc(void)
{
	if(map_file)
		free(map_file);
	if(map_model)
	{
		delete_GL_NETLizard_3D_Model(map_model);
		free(map_model);
	}
	nlSetResourcePath(game, NULL);
	if(ev)
	{
		NETLizard_DeleteEvent(ev, ev_count);
		ev = NULL;
		ev_count = 0;
	}
	bg.tex = NULL;
	delete_scene_2d(&bg);
	delete_game_character(&player);
}

void Viewer_UpdatePlayerPosition(void)
{
	// myself caillyn model
	// get position and angle
	nl_vector3_t ori_v = {player.position[0], player.position[1], player.position[2] + player.height};
	double per = (double)(time - player.ai.time) / 1000.0;
	float turn_unit = player.turn_unit * per;
	float move_unit = player.move_unit * per;

	float oxr = player.x_angle;
	float oyr = player.y_angle;

	orientation_type o = center_orientation_type;
	position_type p = center_position_type;
	if(player.ai.action & aiaction_turnup_type)
		o |= up_orientation_type;
	if(player.ai.action & aiaction_turndown_type)
		o |= down_orientation_type;
	if(player.ai.action & aiaction_turnleft_type)
		o |= left_orientation_type;
	if(player.ai.action & aiaction_turnright_type)
		o |= right_orientation_type;

	if(player.ai.action & aiaction_moveforward_type)
		p |= forward_position_type;
	if(player.ai.action & aiaction_movebackward_type)
		p |= backward_position_type;
	if(player.ai.action & aiaction_moveleft_type)
		p |= left_position_type;
	if(player.ai.action & aiaction_moveright_type)
		p |= right_position_type;
	if(is_cross)
	{
		if(player.ai.action & aiaction_moveup_type)
			p |= up_position_type;
		if(player.ai.action & aiaction_movedown_type)
			p |= down_position_type;
	}

	// get return var
	float ryr = 0.0;
	float rxr = 0.0;
	nl_vector3_t rv = ori_v;

	Algo_TransformPositionAndAngle(p, &ori_v, move_unit, &rv, o, oxr, oyr, turn_unit, &rxr, &ryr, is_cross);

	if(o != center_orientation_type)
	{
		player.y_angle = ryr;
		player.x_angle = rxr;
	}

	if(is_cross)
	{
		player.position[0] = rv.x;
		player.position[1] = rv.y;
		player.position[2] = rv.z - player.height;
		return;
	}

	// whatever must update position, ex. on the elevator
	// check is jumping or falldown
	if(player.z_moving.state != no_z_type)
	{
		double delta = (double)(time - player.z_moving.start_time) / 1000.0;
		rv.z += -Physics_GetFalldownDistance(player.z_moving.jump_speed, GAME_G, delta);
		player.z_moving.speed = Physics_GetJumpSpeed(player.z_moving.jump_speed, GAME_G, delta);
	}
	// collision testing
	nl_vector3_t v = ori_v;
	Algo_ComputeCharacterPositionInNETLizard3DMap(map_model, &player, &rv, &v);
	if(player.scene_collision_result)
	{
		float d = rv.z - v.z;
		if(player.z_moving.state != no_z_type)
		{
			if(d > 0 || player.z_moving.speed < 0.0)
				v.z = rv.z;
			else
			{
				player.z_moving.speed = 0.0;
				player.z_moving.state = no_z_type;
			}
		}
		else
		{
			if(d >= move_unit)
			{
				player.z_moving.state = z_falldown_type;
				player.z_moving.start_z = ori_v.z;
				player.z_moving.start_time = time;
				player.z_moving.jump_speed = 0.0;
				player.z_moving.speed = 0.0;
				v.z = rv.z;
			}
		}
	}
	else
	{
		if(player.z_moving.state == z_jumping_type)
		{
			player.z_moving.state = z_falldown_type;
			player.z_moving.start_z = ori_v.z;
			player.z_moving.start_time = time;
			player.z_moving.jump_speed = 0.0;
			player.z_moving.speed = 0.0;
		}
		else if(player.z_moving.state == z_falldown_type)
		{
			player.z_moving.speed = 0.0;
			player.z_moving.state = no_z_type;
		}
		v.z = ori_v.z;
	}
	player.position[0] = v.x;
	player.position[1] = v.y;
	player.position[2] = v.z - player.height;
	player.current_weapon.position[0] = player.position[0];
	player.current_weapon.position[1] = player.position[1];
	player.current_weapon.position[2] = player.position[2] + player.height;
	player.current_weapon.x_angle = player.x_angle;
	player.current_weapon.y_angle = player.y_angle;
	if(player.z_moving.state != no_z_type && (player.ai.action & aiaction_jump_type) == 0)
		player.ai.action |= aiaction_jump_type;
	else if(player.z_moving.state == no_z_type && player.ai.action & aiaction_jump_type)
		player.ai.action ^= aiaction_jump_type;
}

void Viewer_UpdateGLTransform(game_character *gamer)
{
	if(!gamer)
		return;
	x_t_3d = -gamer -> position[0];
	y_t_3d = -gamer -> position[2] - gamer -> height;
	z_t_3d = gamer -> position[1];
	x_r_3d = gamer -> x_angle;
	y_r_3d = Algo_FormatAngle(-gamer -> y_angle - 180.0);

	if(p_mode == third_person_mode)
	{
		gl_vector3_t third = {0.0, 0.0, 0.0};
		//if(Algo_UpdateThirdPersonPosition(&third.x, &third.y, &third.z, x_t_3d, y_t_3d, z_t_3d, x_r_3d, y_r_3d, -27.0, 15.0, 180.0, gamer -> scene, gamer -> scene_collision_result))
		float rxr = 0.0;
		float ryr = 0.0;

		if(view_free_mode)
		{
			float r = turn_unit_3d * (float)((double)(time - player.ai.time) / 1000.0);
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
}

int Viewer_UpdatePlayerAI(Game_Action a, int p)
{
	if(a == Total_Action)
		return 0;
	if(player.ai.action & aiaction_dead_type)
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
		case MoveUp_Action:
			if((!p && (player.ai.action & aiaction_moveup_type)) || (p && (player.ai.action & aiaction_moveup_type) == 0))
				player.ai.action ^= aiaction_moveup_type;
			break;
		case MoveDown_Action:
			if((!p && (player.ai.action & aiaction_movedown_type)) || (p && (player.ai.action & aiaction_movedown_type) == 0))
				player.ai.action ^= aiaction_movedown_type;
			break;
		case TurnLeft_Action:
			if((!p && (player.ai.action & aiaction_turnleft_type)) || (p && (player.ai.action & aiaction_turnleft_type) == 0))
				player.ai.action ^= aiaction_turnleft_type;
			break;
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
			if(p)
			{
				player.ai.action |= aiaction_attack_type;
			}
			else
			{
				if(player.ai.action & aiaction_attack_type)
					player.ai.action ^= aiaction_attack_type;
			}
			break;
		case Jump_Action:
			if(p)
			{
				if(player.z_moving.state == no_z_type)
				{
					player.z_moving.state = z_jumping_type;
					player.z_moving.start_z = player.position[2];
					player.z_moving.start_time = time;
					player.z_moving.jump_speed = -player.z_jump_speed;
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
		default:
			r = 0;
			break;
	}
	return r;
}

int Viewer_NETLizard3DMapIdleEventFunc(void)
{
	time = Game_GetGameTime();
	Viewer_UpdatePlayerPosition();

	Game_CharacterPlayAnimation(&player, time, fps, delta_time);
	//Mode_DeathGameModeMain(&game_mode, fps);

	Viewer_UpdateGLTransform(&player);
	Viewer_HandleNETLizard3DMapEvent(delta_time);
	player.ai.time = time;

	return 1;
}

int Viewer_NETLizard3DMapKeyFunc(int key, int a, int pressed, int x, int y)
{
	int res = 0;
	switch(key)
	{
		case Harmattan_K_5:
			if(pressed)
			{
				tp_y_offset--;
				res |= 1;
			}
			break;
		case Harmattan_K_6:
			if(pressed)
			{
				tp_y_offset++;
				res |= 1;
			}
			break;
		case Harmattan_K_7:
			if(pressed)
			{
				tp_x_offset--;
				res |= 1;
			}
			break;
		case Harmattan_K_8:
			if(pressed)
			{
				tp_x_offset++;
				res |= 1;
			}
			break;
		case Harmattan_K_9:
			if(pressed)
			{
				tp_dis -= 10;
				res |= 1;
			}
			break;
		case Harmattan_K_0:
			if(pressed)
			{
				tp_dis += 10;
				res |= 1;
			}
			break;
		case Harmattan_K_v:
			if(pressed)
			{
				Viewer_LoadNETLizard3DMapEvent();
			}
			break;
		case Harmattan_K_Control_R:
			if(pressed)
			{
				is_cross ^= 1;
				float x = Algo_FormatAngle(x_r_3d);
				if(!is_cross && (x > 90 && x < 270))
					x_r_3d = 0;
				res = True;
			}
			break;
		case Harmattan_K_f:
			if(pressed)
			{
				if(oglIsEnabled(GL_FOG))
					oglDisable(GL_FOG);
				else
					oglEnable(GL_FOG);
				res |= 1;
			}
			break;
		case Harmattan_K_l:
			if(pressed)
			{
				is_lighting ^= 1;
				res |= 1;
			}
			break;
		default:
			break;
	}
	res |= Viewer_UpdatePlayerAI(a, pressed);
	switch(a)
	{
		case ConsoleMode_Action:
			if(pressed)
			{
				dbg ^= 1;
				res |= 1;
			}
			break;
		case Quit_Action:
			if(pressed)
			{
				Main3D_Shutdown();
				res |= 1;
			}
			break;
		case PersonMode_Action:
			if(pressed)
			{
				p_mode ^= third_person_mode;
				res |= 1;
			}
			break;
		default:
			break;
	}
	return res;
}

void Viewer_NETLizard3DMapReshapeFunc(int w, int h)
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

void Viewer_Init3DFunc(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_SMOOTH);
	oglEnable(GL_TEXTURE_2D);
#ifdef _HARMATTAN_OPENGLES2
	gl2Enable(GL_ALPHA_TEST);
#else
	oglEnable(GL_ALPHA_TEST);
#endif
	glAlphaFunc(GL_GREATER, 0.1);

	glCullFace(GL_BACK);
	oglEnable(GL_CULL_FACE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	oglEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Viewer_HandleNETLizard3DMapEvent(float delta)
{
	if(!ev)
		return;
	int e;
	for(e = 0; e < ev_count; e++)
	{
		if(ev[e].event_type == Event_DoorV)
		{
			nl_vector3_t pos = {player.position[0], player.position[1], player.position[2]};
			GL_NETLizard_3D_Item_Mesh *model = map_model -> item_meshes + ev[e].doorv_event.item_id;
			aabb_t aabb = {
				{model -> item_mesh.ortho[3] + model -> pos[0] - player.width, model -> item_mesh.ortho[4] + model -> pos[1] - player.width, 0},
				{model -> item_mesh.ortho[0] + model -> pos[0] + player.width, model -> item_mesh.ortho[1] + model -> pos[1] + player.width, 0}
			};
			if(Math3D_PointInAABB2D(&pos, &aabb) || (player.collision_item != -1 && ev[e].doorv_event.item_id == player.collision_item))
			{
				NETLizard_HandleDoorEvent(map_model, &(ev[e].doorv_event), 1, delta);
			}
			else
			{
				NETLizard_HandleDoorEvent(map_model, &(ev[e].doorv_event), 0, delta);
			}
		}
		else if(ev[e].event_type == Event_Double_DoorV)
		{
			nl_vector3_t pos = {player.position[0], player.position[1], player.position[2]};
			GL_NETLizard_3D_Item_Mesh *model = map_model -> item_meshes + ev[e].double_doorv_event.item_id;
			GL_NETLizard_3D_Item_Mesh *model2 = map_model -> item_meshes + ev[e].double_doorv_event.item_id_pair;
			nl_vector3_t minv = {0.0, 0.0, 0.0};
			nl_vector3_t maxv = {0.0, 0.0, 0.0};
			minv.x = KARIN_MIN(model -> item_mesh.ortho[3] + model -> pos[0] - player.width, model2 -> item_mesh.ortho[3] + model2 -> pos[0] - player.width);
			minv.y = KARIN_MIN(model -> item_mesh.ortho[4] + model -> pos[1] - player.width, model2 -> item_mesh.ortho[4] + model2 -> pos[1] - player.width);
			minv.z = KARIN_MIN(model -> item_mesh.ortho[5] + model -> pos[2], model2 -> item_mesh.ortho[5] + model2 -> pos[2]);
			maxv.x = KARIN_MAX(model -> item_mesh.ortho[0] + model -> pos[0] + player.width, model2 -> item_mesh.ortho[0] + model2 -> pos[0] + player.width);
			maxv.y = KARIN_MAX(model -> item_mesh.ortho[1] + model -> pos[1] + player.width, model2 -> item_mesh.ortho[1] + model2 -> pos[1] + player.width);
			maxv.z = KARIN_MAX(model -> item_mesh.ortho[2] + model -> pos[2], model2 -> item_mesh.ortho[2] + model2 -> pos[2]);
			aabb_t aabb = {minv, maxv};
			if(Math3D_PointInAABB(&pos, &aabb) || (player.collision_item != -1 && (ev[e].double_doorv_event.item_id == player.collision_item || ev[e].double_doorv_event.item_id_pair == player.collision_item)))
			{
				NETLizard_HandleDoubleVDoorEvent(map_model, &(ev[e].double_doorv_event), 1, delta);
			}
			else
			{
				NETLizard_HandleDoubleVDoorEvent(map_model, &(ev[e].double_doorv_event), 0, delta);
			}
		}
		else if(ev[e].event_type == Event_Double_DoorH)
		{
			nl_vector3_t pos = {player.position[0], player.position[1], player.position[2]};
			GL_NETLizard_3D_Item_Mesh *model = map_model -> item_meshes + ev[e].double_doorh_event.item_id;
			GL_NETLizard_3D_Item_Mesh *model2 = map_model -> item_meshes + ev[e].double_doorh_event.item_id_pair;
			nl_vector3_t minv = {0.0, 0.0, 0.0};
			nl_vector3_t maxv = {0.0, 0.0, 0.0};
			minv.x = KARIN_MIN(model -> item_mesh.ortho[3] + model -> pos[0] - player.width, model2 -> item_mesh.ortho[3] + model2 -> pos[0] - player.width);
			minv.y = KARIN_MIN(model -> item_mesh.ortho[4] + model -> pos[1] - player.width, model2 -> item_mesh.ortho[4] + model2 -> pos[1] - player.width);
			minv.z = KARIN_MIN(model -> item_mesh.ortho[5] + model -> pos[2], model2 -> item_mesh.ortho[5] + model2 -> pos[2]);
			maxv.x = KARIN_MAX(model -> item_mesh.ortho[0] + model -> pos[0] + player.width, model2 -> item_mesh.ortho[0] + model2 -> pos[0] + player.width);
			maxv.y = KARIN_MAX(model -> item_mesh.ortho[1] + model -> pos[1] + player.width, model2 -> item_mesh.ortho[1] + model2 -> pos[1] + player.width);
			maxv.z = KARIN_MAX(model -> item_mesh.ortho[2] + model -> pos[2], model2 -> item_mesh.ortho[2] + model2 -> pos[2]);
			aabb_t aabb = {minv, maxv};
			if(Math3D_PointInAABB(&pos, &aabb) || (player.collision_item != -1 && (ev[e].double_doorh_event.item_id == player.collision_item || ev[e].double_doorh_event.item_id_pair == player.collision_item)))
			{
				NETLizard_HandleDoubleHDoorEvent(map_model, &(ev[e].double_doorh_event), 1, delta);
			}
			else
			{
				NETLizard_HandleDoubleHDoorEvent(map_model, &(ev[e].double_doorh_event), 0, delta);
			}
		}
		else if(ev[e].event_type == Event_Elevator)
		{
			nl_vector3_t pos = {player.position[0], player.position[1], player.position[2]};
			GL_NETLizard_3D_Item_Mesh *model = map_model -> item_meshes + ev[e].elevator_event.item_id;
			aabb_t aabb = {
				{model -> item_mesh.ortho[3] + model -> pos[0], model -> item_mesh.ortho[4] + model -> pos[1], ev[e].elevator_event.min_z},
				{model -> item_mesh.ortho[0] + model -> pos[0], model -> item_mesh.ortho[1] + model -> pos[1], ev[e].elevator_event.max_z + 2}
			};
			if(Math3D_PointInAABB(&pos, &aabb))
			{
				NETLizard_HandleElevatorEvent(map_model, &(ev[e].elevator_event), 1, delta);
			}
			else
			{
				//NETLizard_HandleElevatorEvent(map_model, &(ev[e].elevator_event), 0, delta);
			}
		}
		else if(ev[e].event_type == Event_Fan)
		{
			NETLizard_HandleFanEvent(map_model, &(ev[e].fan_event), 1, delta);
		}
		else if(ev[e].event_type == Event_Prop)
		{
			NETLizard_HandlePropEvent(map_model, &(ev[e].prop_event), 1, delta);
		}
		else if(ev[e].event_type == Event_Machine)
		{
			nl_vector3_t pos = {player.position[0], player.position[1], player.position[2] + player.height};

			GL_NETLizard_3D_Item_Mesh *model = map_model -> item_meshes + ev[e].machine_event.machine_gun_event.item_id;
			nl_vector3_t pos2 = {model -> pos[0], model -> pos[1], model -> pos[2] - 125};
			float d = 0.0;
			int r = Algo_PointCanViewPointInNETLizard3DMap(map_model, &pos, &pos2, &d);
			if(r && (ev[e].machine_event.machine_gun_event.range < 0 || d <= ev[e].machine_event.machine_gun_event.range))
			{
				ev[e].machine_event.target_x = player.position[0];
				ev[e].machine_event.target_y = player.position[1];
				ev[e].machine_event.target_z = player.position[2] + player.height;
				NETLizard_HandleMachineEvent(map_model, &(ev[e].machine_event), 1, 1, delta);
			}
			else
			{
				NETLizard_HandleMachineEvent(map_model, &(ev[e].machine_event), 0, 0, delta);
			}
		}
		else if(ev[e].event_type == Event_Portal && player.collision_item != -1 && ev[e].portal_event.item_id == player.collision_item)
		{
			if(ev[e].portal_event.mask & 1)
				player.position[0] = ev[e].portal_event.xt;
			if(ev[e].portal_event.mask & (1 << 1))
				player.position[1] = ev[e].portal_event.yt;
			if(ev[e].portal_event.mask & (1 << 2))
				player.position[2] = ev[e].portal_event.zt - (2293760 >> 16);
		}
	}
}

void Viewer_LoadNETLizard3DMapEvent(void)
{
	if(ev)
	{
		NETLizard_DeleteEvent(ev, ev_count);
		ev = NULL;
		ev_count = 0;
	}
	if(level != -1)
	{
		ev = NETLizard_LoadEventFile(EVENT_FILE, game, level, &ev_count);
	}
}
