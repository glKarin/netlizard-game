#include "netlizard_viewer.h"
#include "glk/glk.h"
#include "gl_3d_main.h"
#include "nl_algo.h"
#include "gl_util.h"
#include "SOIL/SOIL.h"
#include "nl_gl.h"
#include "game_util.h"
#include "math3d/algo.h"
#include "cross_hair.h"

#include "netlizard/nl_util.h"
#include "netlizard/texture_v2_reader.h"

#define PAGE_NAME "NETLizard3DItemViewer"

// o/o obj/obj

#define COLLISION_WIDTH 60
#define COLLISION_HEIGHT 150

#define SKY_FILE _KARIN_RESOURCE_DIR"resource/sky1.png"
#define FP_FILE _KARIN_RESOURCE_DIR"resource/c0.png"

#include "ada.h"
ADA_GL_Model ada;
ADA_pmd pmd;

#include "csol/studio_game.h"

static GameStudioModel mdl;
//static float frustum[6][4];

static game_name game;
static char *item_file = NULL;

static bool_t dbg = 1;

static scene_2d bg;
static cross_hair fps_cross_hair;
static GL_NETLizard_3D_Model *item_model = NULL;
static unsigned int level;

static void Viewer_InitFunc(void);
static void Viewer_DrawFunc(void);
static void Viewer_FreeFunc(void);
static int Viewer_IdleFunc(void);
static void Viewer_ReshapeFunc(int w, int h);
static int Viewer_KeyFunc(int key, int a, int pressed, int x, int y);
static Main3DStoreFunction_f Viewer_StoreFunc = NULL;
static Main3DRestoreFunction_f Viewer_RestoreFunc = NULL;
static Main3DMouseMotionFunction Viewer_MotionFunc = NULL;
static Main3DMouseFunction Viewer_MouseFunc = NULL;
static Main3DMouseClickFunction Viewer_ClickFunc = NULL;

int Viewer_NETLizard3DItemInitMain(const char *g, const char *d, const char *src, unsigned int lvl)
{
	if(!g)
		return 0;
	const char *prefix = NULL;
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
		item_file = strdup(src);
	}
	else
	{
		switch(game)
		{
			case nl_contr_terrorism_3d:
				prefix = "obj/obj";
				break;
			case nl_contr_terrorism_3d_episode_2:
			case nl_contr_terrorism_3d_episode_3:
			case nl_army_ranger_3d:
			case nl_shadow_of_egypt_3d:
			case nl_clone_3d:
				prefix = "o/o";
				break;
			default:
				free(dir);
				return 0;
		}
		size_t l = (lvl >= 10 ? 2 : 1);
		size_t len = strlen(dir) + 1 + strlen(prefix) + l + 4 + 1;
		item_file = NEW_II(char, len);
		sprintf(item_file, "%s/%s%d.png", dir, prefix, lvl);
		level = lvl;
	}
	nlSetResourcePath(game, dir);
	free(dir);
	return 1;
}

void Viewer_NETLizard3DItemRegisterFunction(void)
{
	glk_function func;

	func = REGISTER_RENDER_FUNCTION(Viewer);
	Main3D_InitRenderPage(PAGE_NAME, &func);
}

void Viewer_InitFunc(void)
{
	Viewer_Init3DFunc();
	is_cross = GL_TRUE;
	//glClearColor(0.0, 0.0, 0.0 ,1.0);
	oglDisable(GL_CULL_FACE);
	move_unit_3d = 10;
	turn_unit_3d = 10;
	x_a_3d = -90;
	z_t_3d = -400;
	y_t_3d = -100;
	viewport_width = 400;
	viewport_height = 240;

	new_scene_2d(&bg, 0.0f, 0.0f, 854.0f, 480.0f, 1.0, left_bottom_anchor_type, Color_GetColor(white_color, 0.0), NULL);

	bg.tex = new_texture_from_nl_v2_3d_file(SKY_FILE);

	new_normal_cross_hair(&fps_cross_hair, cross_type, X11_COLOR(white), 20, 2, 50);

	{
		printfs(item_file);
		switch(game)
		{
			case nl_contr_terrorism_3d:
				item_model = NETLizard_ReadGLCT3DItemModelFile(item_file, level);
				break;
			case nl_army_ranger_3d:
				item_model = NETLizard_ReadGLSpecnaz3DItemModelFile(item_file, level);
				break;
			case nl_contr_terrorism_3d_episode_2:
				item_model = NETLizard_ReadGLCT3DEp2ItemModelFile(item_file, level);
				break;
			case nl_shadow_of_egypt_3d:
				item_model = NETLizard_ReadGLEgypt3DItemModelFile(item_file, level);
				break;
			case nl_clone_3d:
				item_model = NETLizard_ReadGLClone3DItemModelFile(item_file, level);
				break;
			case nl_contr_terrorism_3d_episode_3:
				item_model = NETLizard_ReadGLCT3DEp3ItemModelFile(item_file, level);
				break;
			default:
				break;
		}
		if(item_model)
		{
			NETLizard_MakeGL23DModel(item_model);
		}
		else
			return;
	}

	char *pmds[] = {
		"xfile/pl0b/pl0b0a.pmd",
		"xfile/pl0b/pl0b0b.pmd",
		"xfile/pl0b/pl0b0c.pmd",
		"xfile/pl0b/pl0blh00.pmd",
		"xfile/pl0b/pl0brh00.pmd",
		"xfile/pl0b/pl0b0d.pmd",
		"xfile/pl0b/pl0b0h.pmd",
		"xfile/pl0b/pl0blh01.pmd",
		"xfile/pl0b/pl0blh02.pmd",
		"xfile/pl0b/pl0blh04.pmd",
		"xfile/pl0b/pl0brh01.pmd",
		"xfile/pl0b/pl0brh02.pmd",
		"xfile/pl0b/pl0brh03.pmd",
		"xfile/pl0b/pl0brh04.pmd",
		"xfile/pl0b/pl0brh06.pmd",
		"xfile/pl0b/pl0brh07.pmd",
		NULL
	};
	printfi(Ada_LoadPmdModel(&ada, pmds, 1, "xfile/pl0b"));
	Ada_ReadPmdFile(&pmd, "xfile/pl0b/pl0b0a.pmd");

	memset(&mdl, 0, sizeof(GameStudioModel));
	//bool b = Init(&mdl, "natasha2.mdl");
	bool b = CSOL_LoadMDL(&mdl, "resource/model/Girl/natasha2.mdl");
	printf("%d\n", b);
	if(!b)
		exit(EXIT_FAILURE);
	int anim;
	CSOL_GetSequence(&mdl, "walk", &anim);
	CSOL_SetSequence(&mdl, LEG_PART, anim);
	CSOL_GetSequence(&mdl, "ref_reload_rifle", &anim);
	CSOL_SetSequence(&mdl, BODY_PART, anim);
}

void Viewer_DrawFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(!item_model)
		return;
	if(1)
	{
		OpenGL_Render2D(0.0, width, 0.0, height);
		{
			UI_RenderScene2D(&bg);
		}
	}

	OpenGL_Render3D(45, width, height, 0.25, 3000);
	{
		glPushMatrix();
		{
			Main3D_ModelViewTransform(first_person_mode, 0.0, 0.0, 0.0, 0);

			glPushMatrix();
			{
				//NETLizard_RenderGL3DModel(item_model);
				//glScalef(10, 10, 10);
				//Ada_RenderStaticModel(&ada);
				//arb(&pmd);
				CSOL_SetFrame(&mdl, BODY_PART, CSOL_AdvanceFrame(&mdl, BODY_PART, delta_time));
				CSOL_SetFrame(&mdl, LEG_PART, CSOL_AdvanceFrame(&mdl, LEG_PART, delta_time));
				CSOL_DrawModel(&mdl);
				/*
				SetUpBones(&mdl);
				DrawBones(&mdl);
				DrawHitboxes(&mdl);
				*/
				glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
			if(is_cross)
				Font_RenderString(&fnt, 0, 4 * fnt.height, 0.0, 0.0, 0.0, 1.0, "cross");
			Font_RenderString(&fnt, 0, height - 2 * fnt.height, 0.0, 0.0, 0.0, 1.0, item_file);
		}
	}
}

void Viewer_FreeFunc(void)
{
	if(item_file)
		free(item_file);
	if(item_model)
	{
		delete_GL_NETLizard_3D_Model(item_model);
		free(item_model);
	}
	nlSetResourcePath(game, NULL);
	delete_scene_2d(&bg);
}

int Viewer_IdleFunc(void)
{
	/*
		 int i;
		 for(i = 0; i < item_model->item_meshes[0].item_mesh.plane_count; i++)
		 {
		 printfi(i);
		 printfv3(*((vector3_t *)(item_model->item_meshes[0].item_mesh.plane[i].normal)));
		 }
		 */
	// 测面 （1 0 0）
	// 正面 （0 1 0）
	// 上面 （0 0 1）

	return Main3D_BaseTransform();
}

int Viewer_KeyFunc(int key, int a, int pressed, int x, int y)
{
	int res = 0;
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

void Viewer_ReshapeFunc(int w, int h)
{
#ifndef _HARMATTAN_OPENGL
	glViewport(0, 0, w, h);
#else
	glViewport( (w - viewport_width) / 2, (h - viewport_height) / 2, viewport_width, viewport_height);
#endif
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	UI_ResizeScene2D(&bg, w, h);
}

