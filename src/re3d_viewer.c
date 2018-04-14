#include "netlizard_viewer.h"
#include "glk/glk.h"
#include "gl_3d_main.h"
#include "gl_util.h"
#include "SOIL/SOIL.h"
#include "nl_gl.h"
#include "nl_algo.h"
#include "game_util.h"

#include "netlizard/nl_util.h"
#include "netlizard/png_reader.h"

#define COLLISION_WIDTH 60
#define COLLISION_HEIGHT 150

static GLfloat frustum[6][4];

static game_name game;
static char *map_file = NULL;
static char *car_file = NULL;
static char *car_tex_file = NULL;
static char *mode = NULL;

static scene_2d bg;
static bool_t dbg = 1;
static bool_t test = 0;

static GL_RE3D_Model *model = NULL;
static unsigned int level;

static void Viewer_RE3DInitFunc(void);
static void Viewer_RE3DDrawFunc(void);
static void Viewer_RE3DFreeFunc(void);
static int Viewer_RE3DIdleEventFunc(void);
static int Viewer_RE3DKeyEventFunc(int key, int act, int pressed, int x, int y);
static void Viewer_RE3DReshapeFunc(int w, int h);
static void Viewer_RE3DInitSimpleLight(void);

void Viewer_RE3DInitSimpleLight(void)
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
		-60.0f, -10.0f, 40.0f, 0.0
	};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	/*
	GLfloat spot_directory[] = {
		1.0, 1.0, -1.0
	};
	GLfloat spot_cutoff = 40.0f;
	GLfloat spot_exponent = 3.0f;
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_directory);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
	*/

	GLfloat material_specular[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};
	GLfloat material_ambient_and_diffuse[] = {
		0.8f, 0.8f, 0.8f, 1.0f
	};
	GLfloat material_shiness[] = {
		60.0f
	};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_ambient_and_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, *material_shiness);

	GLfloat global_ambient_light[] = {
		0.8f, 0.8f, 0.8f, 1.0f
	};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient_light);
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

	oglEnable(GL_LIGHT0);
	//oglEnable(GL_LIGHTING);
#endif
}

void Viewer_RE3DRegisterFunction(void)
{
	Main3D_SetInitFunction(Viewer_RE3DInitFunc);
	Main3D_SetDrawFunction(Viewer_RE3DDrawFunc);
	Main3D_SetFreeFunction(Viewer_RE3DFreeFunc);
	Main3D_SetKeyEventFunction(Viewer_RE3DKeyEventFunc);
	Main3D_SetIdleEventFunction(Viewer_RE3DIdleEventFunc);
	Main3D_SetReshapeFunction(Viewer_RE3DReshapeFunc);
	Main3D_SetMouseEventFunction(NULL);
	Main3D_SetMouseMotionEventFunction(NULL);
	Main3D_SetMouseClickEventFunction(NULL);
}

int Viewer_RE3DInitMain(const char *g, const char *m, const char *d, const char *src, unsigned int lvl)
{
	if(!g || !m)
		return 0;
	char *dir = NULL;
	if(d)
		dir = strdup(d);
	else
		dir = strdup(".");
	if(strcasecmp(g, "re3d") == 0)
		game = nl_racing_evolution_3d;
	else
	{
		free(dir);
		return 0;
	}
	if(strcasecmp(m, "map") == 0)
	{
		if(src)
		{
			map_file = strdup(src);
		}
		else
		{
			size_t len = strlen(dir) + 1 + 6 + 1 + 4 + 1;
			map_file = NEW_II(char, len);
			sprintf(map_file, "%s/"RE3D_LEVEL_FILE_SUBFIX, dir, lvl);
			level = lvl;
		}
		mode = strdup(m);
	}
	else if(strcasecmp(m, "car") == 0)
	{
		int car_mesh;
		if(lvl == 2)
			car_mesh = 1;
		else if(lvl == 4)
			car_mesh = 3;
		else if(lvl == 6)
			car_mesh = 5;
		else
			car_mesh = lvl;
		if(src)
		{
			car_file = strdup(src);
		}
		else
		{
			size_t len = strlen(dir) + 1 + 3 + 1 + 4 + 1; 
			car_file = NEW_II(char, len);
			sprintf(car_file, "%s/"RE3D_CAR_FILE_SUBFIX, dir, car_mesh);
		}
		size_t len = strlen(dir) + 1 + 3 + 1 + 4 + 4 + 1; 
		car_tex_file = NEW_II(char, len);
		sprintf(car_tex_file, "%s/car%d_tex.png", dir, lvl);
		level = lvl;
		mode = strdup(m);
	}
	else
	{
		free(dir);
		Viewer_RE3DFreeFunc();
		return 0;
	}

	nlSetResourcePath(game, dir);
	free(dir);
	return 1;
}

void Viewer_RE3DInitFunc()
{
	Viewer_Init3DFunc();
	is_cross = GL_TRUE;
	GLfloat color[] = {1.0f, 1.0f, 1.0f, 1.0f};
	OpenGL_InitSimpleFog(50.0f, 100.0f, 0.01f, color);
	oglEnable(GL_FOG);
#ifndef _HARMATTAN_OPENGLES2
	Viewer_RE3DInitSimpleLight();
#endif
	viewport_width = 400;
	viewport_height = 240;
	move_unit_3d = 2;
	turn_unit_3d = 5;

	GLfloat bg_color[] = {0.0, 0.0, 0.0, 1.0};
	new_scene_2d(&bg, 0.0f, 0.0f, 854.0f, 480.0f, 1.0, left_bottom_anchor_type, bg_color, NULL);

	//fp.tex = new_OpenGL_texture_2d(FP_FILE);

	if(strcasecmp(mode, "map") == 0)
		model = NETLizard_ReadGLRE3DModelFile(map_file);
	else if(strcasecmp(mode, "car") == 0)
		model = NETLizard_ReadGLRE3DCarModelFile(car_file, car_tex_file);
	else
		return;
	if(model)
		bg.tex = model -> bg_tex;

	printfs(map_file);
	printfs(car_file);
	printfs(car_tex_file);
}

void Viewer_RE3DDrawFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int *scenes = NULL;
	unsigned int count = 0;

	if(bg.tex)
	{
		OpenGL_Render2D(0.0, width, 0.0, height);
		{
			UI_RenderScene2D(&bg);
		}
	}

	OpenGL_Render3D(45, width, height, 0.25, 200);
	{
		glPushMatrix();
		{
			Main3D_ModelViewTransform(first_person_mode, 0.0, 0.0, 0.0, 0);
			glPushMatrix();
			{
				OpenGL_ExtractFrustum(frustum);
				scenes = Algo_GetRE3DMapRenderScenes(model, &count, frustum);
				if(scenes)
				{
					NETLizard_RenderGLRE3DModelScene(model, scenes, count);
				}
				else
					NETLizard_RenderGLRE3DModel(model);
#if 0
				if(test)
				{
					glPointSize(8);
					//GLfloat f = 1.0 / (model -> count + 1);
					int i;
					for(i = 0; i < 1; i++)
					{
						glBegin(GL_POINTS);
						{
							glColor3f(0, 0, 1);
							glVertex3f(model -> meshes[i].ortho[3], model -> meshes[i].ortho[4], model -> meshes[i].ortho[5]);
							glColor3f(1, 0, 0);
							glVertex3f(model -> meshes[i].ortho[0], model -> meshes[i].ortho[1], model -> meshes[i].ortho[2]);
						}
						glEnd();
					}
					glColor3f(1.0, 1.0, 1.0);
				}
#endif
			}
			glPopMatrix();
		}
		glPopMatrix();
	}

	/*
		 OpenGL_Render3D(45, width, height, 0.25, 5000);
		 {
		 glPushMatrix();
		 {
	//glRotatef(x_r,1,0,0);
	//glRotatef(y_r,0,1,0);

	glTranslatef(-100, -150, -300);

	glScalef(0.3, 0.3, 0.3);
	glRotatef(90,0,1,0);
	glRotatef(yAxisRotate,0,1,0);
	glRotatef(xAxisRotate,1,0,0);

	glPushMatrix();
	{
	GLfloat y = ator(y_r);
	GLfloat x = ator(x_r);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(cos(x) * sin(y), // x
	sin(x), // y
	-cos(x) * cos(y) // z
	);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	//NETLizard_RenderGLRE3DModel(model);
	static GLuint anim = 0;
	static GLuint frame = 0;
	//NETLizard_RenderGL3DAnimationModel(role_model, anim, frame);
	frame++;
	if(frame >= clone3d_role_model -> anim_frame_count[anim])
	frame = 0;
	}
	glPopMatrix();
	}
	glPopMatrix();
	}
	*/

	OpenGL_Render2D(0.0, width, 0.0, height);
	{
		if(dbg)
		{
			char str[50];
			memset(str, '\0', 50 * sizeof(char));
			sprintf(str, "Pos -> (%.2f, %.2f, %.2f)", x_t_3d, y_t_3d, z_t_3d);
			Font_RenderString(&fnt, 0, 0, 0.0, 0.0, 0.0, 1.0, str);
			sprintf(str, "Ang -> (%.2f, %.2f)", y_r_3d, x_r_3d);
			Font_RenderString(&fnt, 0, 2 * fnt.height, 0.0, 0.0, 0.0, 1.0, str);
			sprintf(str, "%s%s", is_cross ? "C " : "", 
#ifndef _HARMATTAN_OPENGLES2
					oglIsEnabled(GL_FOG)
#else
					0
#endif
					? "F " : "");
			Font_RenderString(&fnt, 0, height / 2 - fnt.height, 0.0, 0.0, 0.0, 1.0, str);
			Font_RenderString(&fnt, 0, height - 2 * fnt.height, 0.0, 0.0, 0.0, 1.0, map_file);
			sprintf(str, "Scene -> (%d)", model -> count);
			Font_RenderString(&fnt, 0, 6 * fnt.height, 0.0, 0.0, 0.0, 1.0, str);
			if(scenes)
			{
				unsigned int i;
				for(i = 0; i < count; i++)
					Font_RenderDigit(&fnt, i * (fnt.width * 2), 4 * fnt.height, 0.0, 0.0, 0.0, 1.0, scenes[i]);
			}
		}
	}
	if(scenes)
		free(scenes);
}

void Viewer_RE3DFreeFunc(void)
{
	if(map_file)
		free(map_file);
	if(car_file)
		free(car_file);
	if(car_tex_file)
		free(car_tex_file);
	if(mode)
		free(mode);
	if(model)
	{
		delete_GL_RE3D_Model(model);
		free(model);
	}
	nlSetResourcePath(game, NULL);
}

int Viewer_RE3DIdleEventFunc(void)
{
	return Main3D_BaseTransform();
}

int Viewer_RE3DKeyEventFunc(int key, int a, int pressed, int x, int y)
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
		case ConsoleMode_Action:
			if(pressed)
			{
				dbg ^= 1;
				res |= 1;
			}
			break;
		default:
			break;
	}
	switch(key)
	{
		case Harmattan_K_f:
#ifndef _HARMATTAN_OPENGLES2
			if(pressed)
			{
				if(oglIsEnabled(GL_FOG))
					oglDisable(GL_FOG);
				else
					oglEnable(GL_FOG);
				res |= 1;
			}
#endif
			break;
		case Harmattan_K_l:
#ifndef _HARMATTAN_OPENGLES2
			if(pressed)
			{
				if(oglIsEnabled(GL_LIGHTING))
					oglDisable(GL_LIGHTING);
				else
					oglEnable(GL_LIGHTING);
				res |= 1;
			}
#endif
			break;
		case Harmattan_K_t:
			if(pressed)
			{
				test ^= 1;
				res |= 1;
			}
			break;
		default:
			break;
	}
	return res;
}

GLvoid Viewer_RE3DReshapeFunc(int w, int h)
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

