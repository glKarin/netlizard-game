#include "netlizard_viewer.h"
#include "glk/glk.h"
#include "gl_3d_main.h"
#include "nl_algo.h"
#include "gl_util.h"
#include "SOIL/SOIL.h"
#include "nl_gl.h"
#include "game_util.h"
#include "cross_hair.h"

#include "netlizard/nl_util.h"
#include "netlizard/texture_v2_reader.h"

#define PAGE_NAME "NETLizard3DAnimationViewer"

// un

#define COLLISION_WIDTH 0
#define COLLISION_HEIGHT 150

#define SKY_FILE _KARIN_RESOURCE_DIR"resource/sky1.png"
#define FP_FILE _KARIN_RESOURCE_DIR"resource/c0.png"

static game_name game;
static char *un_file = NULL;
static GLuint anim = 0;
static GLuint frame = 0;

static bool_t dbg = 1;
static bool_t playing = 1;

static scene_2d bg;
static cross_hair fps_cross_hair;
static GL_NETLizard_3D_Animation_Model *role_model = NULL;
static unsigned int level;

static void Viewer_InitFunc(void);
static void Viewer_DrawFunc(void);
static void Viewer_FreeFunc(void);
static int Viewer_IdleFunc(void);
static int Viewer_KeyFunc(int key, int act, int pressed, int x, int y);
static void Viewer_ReshapeFunc(int w, int h);
static Main3DStoreFunction_f Viewer_StoreFunc = NULL;
static Main3DRestoreFunction_f Viewer_RestoreFunc = NULL;
static Main3DMouseMotionFunction Viewer_MotionFunc = NULL;
static Main3DMouseFunction Viewer_MouseFunc = NULL;
static Main3DMouseClickFunction Viewer_ClickFunc = NULL;

int Viewer_NETLizard3DAnimationInitMain(const char *g, const char *d, const char *src, unsigned int lvl, int a)
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
	else if(strcasecmp(g, "clone3d") == 0)
		game = nl_clone_3d;
	else
	{
		free(dir);
		return 0;
	}
	if(src)
	{
		un_file = strdup(src);
	}
	else
	{
		size_t l = (lvl >= 10 ? 2 : 1);
		size_t len = strlen(dir) + 1 + 2 + l + 4 + 1;
		un_file = NEW_II(char, len);
		sprintf(un_file, "%s/"ROLE_FILE_SUBFIX, dir, lvl);
	}
	nlSetResourcePath(game, dir);
	level = lvl;
	anim = a;
	free(dir);
	return 1;
}

void Viewer_NETLizard3DAnimationRegisterFunction(void)
{
	glk_function func;

	func = REGISTER_RENDER_FUNCTION(Viewer);
	Main3D_InitRenderPage(PAGE_NAME, &func);
}

void Viewer_InitFunc(void)
{
	Viewer_Init3DFunc();
	is_cross = GL_TRUE;
	oglDisable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0 ,1.0);
	move_unit_3d = 10;
	turn_unit_3d = 10;

	z_t_3d = -500;
	y_t_3d = -200;

	x_a_3d = -90;
	viewport_width = 400;
	viewport_height = 240;

	new_scene_2d(&bg, 0.0f, 0.0f, 854.0f, 480.0f, 1.0, left_bottom_anchor_type, Color_GetColor(white_color, 0.0), NULL);

	bg.tex = new_texture_from_nl_v2_3d_file(SKY_FILE);

	new_normal_cross_hair(&fps_cross_hair, cross_type, X11_COLOR(white), 20, 2, 50);

	printfs(un_file);
	switch(game)
	{
		case nl_shadow_of_egypt_3d:
			role_model = NETLizard_ReadGLEgypt3DRoleModelFile(un_file, level);
			break;
		case nl_clone_3d:
			role_model = NETLizard_ReadGLClone3DRoleModelFile(un_file, level);
			break;
		default:
			break;
	}
	if(role_model)
	{
		NETLizard_MakeGL23DAnimationModel(role_model);
	}
	else
		return;
}

void Viewer_DrawFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(1)
	{
		OpenGL_Render2D(0.0, width, 0.0, height);
		{
			UI_RenderScene2D(&bg);
		}
	}

	OpenGL_Render3D(45, width, height, 0.25, 2000);
	{
		glPushMatrix();
		{
			Main3D_ModelViewTransform(first_person_mode, 0.0, 0.0, 0.0, 0);

			glPushMatrix();
			{
				NETLizard_RenderGL3DAnimationModel(role_model, anim, frame);
				if(playing)
				{
					frame++;
					if(frame > role_model->animations[anim].end - role_model->animations[anim].begin)
						frame = 0;
				}
			}
			glPopMatrix();
		}
		glPopMatrix();
	}

	OpenGL_Render2D(0.0, width, 0.0, height);
	{
		glPushMatrix();
		{
			glTranslatef(width / 2, height / 2, 0.0f);
			UI_RenderCrossHair(&fps_cross_hair);
		}
		glPopMatrix();

		if(dbg)
		{
			char str[50];
			memset(str, '\0', 50 * sizeof(char));
			sprintf(str, "Pos->(%.2f, %.2f, %.2f)", x_t_3d, y_t_3d, z_t_3d);
			Font_RenderString(&fnt, 0, 0, 0.0, 0.0, 0.0, 1.0, str);
			sprintf(str, "Ang->(%.2f, %.2f)", y_r_3d, x_r_3d);
			Font_RenderString(&fnt, 0, 2 * fnt.height, 0.0, 0.0, 0.0, 1.0, str);
			sprintf(str, "frame->(%d %d - %d / %d)", anim, role_model->animations[anim].begin, frame, role_model->animations[anim].end - role_model->animations[anim].begin);
			Font_RenderString(&fnt, 0, 4 * fnt.height, 0.0, 0.0, 0.0, 1.0, str);
			sprintf(str, "%s", nlGetAnimationName(role_model->animations[anim].type));
			Font_RenderString(&fnt, 0, 6 * fnt.height, 0.0, 0.0, 0.0, 1.0, str);
			Font_RenderString(&fnt, 0, height - 2 * fnt.height, 0.0, 0.0, 0.0, 1.0, un_file);
		}
	}
}

void Viewer_FreeFunc(void)
{
	if(un_file)
		free(un_file);
	if(role_model)
	{
		delete_GL_NETLizard_3D_Animation_Model(role_model);
		free(role_model);
	}
	nlSetResourcePath(game, NULL);
	delete_scene_2d(&bg);
}

void Viewer_ReshapeFunc(int w, int h)
{
#ifdef _HARMATTAN_OPENGLES
	glViewport(0, 0, w, h);
#else
	glViewport( (w - viewport_width) / 2, (h - viewport_height) / 2, viewport_width, viewport_height);
#endif
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	UI_ResizeScene2D(&bg, w, h);
}

int Viewer_IdleFunc(void)
{
	Main3D_BaseTransform();
	return 1;
}

int Viewer_KeyFunc(int key, int a, int pressed, int x, int y)
{
	int res = 0;
	switch(key)
	{
		case Harmattan_K_r:
			if(pressed)
			{
				playing ^= 1;
				res |= 1;
			}
			break;
		case Harmattan_K_n:
			if(pressed)
			{
				playing = 0;
				frame++;
				if(frame > role_model->animations[anim].end - role_model->animations[anim].begin)
					frame = 0;
				res |= 1;
			}
			break;
		case Harmattan_K_p:
			if(pressed)
			{
				playing = 0;
				if(frame == 0)
					frame = 0;
				else
					frame--;
				res |= 1;
			}
			break;
		case Harmattan_K_f:
			if(pressed)
			{
				if(anim == 0)
					anim = 0;
				else
					anim--;
				playing = 1;
				res |= 1;
			}
			break;
		case Harmattan_K_l:
			if(pressed)
			{
				if(anim >= role_model->anim_count - 1)
					anim = 0;
				else
					anim++;
				playing = 1;
				res |= 1;
			}
			break;
		default:
			break;
	}
	switch(a)
	{
		case Quit_Action:
			if(pressed)
			{
				Main3D_Shutdown();
				res |= 1;
			}
			break;
		default:
			break;
	}
	return res;
}

